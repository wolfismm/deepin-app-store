package main

import (
	"encoding/json"
	"strings"

	dbus "pkg.deepin.io/lib/dbus1"
	"pkg.deepin.io/lib/utils"
)

const (
	dbusMetadataInterface = "com.deepin.AppStore.Metadata"
	dbusMetadataPath      = "/com/deepin/AppStore/Metadata"
)

// GetInterfaceName return dbus interface name
func (*Metadata) GetInterfaceName() string {
	return dbusMetadataInterface
}

// GetAppIcon return app local icon path
func (m *Metadata) GetAppIcon(appName string) (string, *dbus.Error) {
	return m.getAppIcon(appName), nil
}

// GetAppMetadataList return app info with changelog
func (m *Metadata) GetAppMetadataList(appNameList []string) (string, *dbus.Error) {
	appList := make([]*AppBody, 0)

	for _, appName := range appNameList {
		app, err := m.getAppMetadata(appName)
		if nil != err {
			continue
		}
		appList = append(appList, app)
	}

	data, _ := json.Marshal(appList)

	return string(data), nil
}

// OpenApp call lastore open app
func (m *Metadata) OpenApp(appName string) *dbus.Error {
	output, _, err := utils.ExecAndWait(3600, "lastore-tools", "querydesktop", appName)
	if nil != err {
		logger.Errorf("call lastore-tools failed: %v", err)
		return dbus.NewError(err.Error(), nil)
	}
	output = strings.TrimSpace(output)

	if "" == output {
		logger.Infof("can not find desktop file")
		return dbus.NewError("no desktop file", nil)
	}

	sysBus, err := dbus.SessionBus()
	if nil != err {
		logger.Errorf("get dbus failed: %v", err)
		return dbus.NewError(err.Error(), nil)
	}
	startManager := sysBus.Object("com.deepin.SessionManager", "/com/deepin/StartManager")
	err = startManager.Call("com.deepin.StartManager.LaunchApp", 0, output, uint32(0), []string{}).Store()
	if nil != err {
		logger.Errorf("call dbus failed: %v", err)
		return dbus.NewError(err.Error(), nil)
	}
	return nil
}

// OnMessage handle push message
func (m *Metadata) OnMessage(playload map[string]interface{}) *dbus.Error {
	logger.Infof("receive message: %v", playload)
	action, ok := playload["action"]
	if !ok {
		logger.Errorf("unknown message %v", playload)
	}

	var err error
	switch action {
	case "install":
		err = m.handleInstall(playload)
	default:
		logger.Warning("unknown action %v", playload)
	}

	if nil != err {
		logger.Errorf("process message failed: %v", playload)
	}

	return nil
}
