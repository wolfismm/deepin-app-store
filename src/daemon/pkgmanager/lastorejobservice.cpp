/*
 * Copyright (C) 2019 ~ 2020 Union Tech Co., Ltd.
 *
 * Author:     zhoutao <zhoutao@uniontech.com>
 *
 * Maintainer: zhoutao <zhoutao@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "lastorejobservice.h"

#include <QtDBus>

LastoreJobService::LastoreJobService(QString path, QObject *parent) :
    QObject(parent),
    m_JobPath(path)
{
    m_pLastoreJob = new LastoreJobManager(path,this);
}

bool LastoreJobService::cancelable()
{
    return m_pLastoreJob->cancelable();
}

qlonglong LastoreJobService::createTime()
{
    return m_pLastoreJob->createTime();
}

QString LastoreJobService::description()
{
    return m_pLastoreJob->description();
}

qlonglong LastoreJobService::downloadSize()
{
    return m_pLastoreJob->downloadSize();
}

QString LastoreJobService::id()
{
    return m_pLastoreJob->id();
}

QString LastoreJobService::name()
{
    return m_pLastoreJob->name();
}

QStringList LastoreJobService::packages()
{
    return m_pLastoreJob->packages();
}

double LastoreJobService::progress()
{
    return m_pLastoreJob->progress();
}

qlonglong LastoreJobService::speed()
{
    return m_pLastoreJob->speed();
}

QString LastoreJobService::status()
{
    return m_pLastoreJob->status();
}

QString LastoreJobService::type()
{
    return m_pLastoreJob->type();
}

QString LastoreJobService::getJobPath()
{
    return m_JobPath;
}

void LastoreJobService::Clean()
{
    emit jobController("CleanJob",m_JobPath);
}

void LastoreJobService::Pause()
{
    emit jobController("PauseJob",m_JobPath);
}

void LastoreJobService::Start()
{
    emit jobController("StartJob",m_JobPath);
}