/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "lyricssettingsmodel.h"

#include "translation.h"

using namespace mu::inspector;

LyricsSettingsModel::LyricsSettingsModel(QObject* parent, IElementRepositoryService* repository)
    : AbstractInspectorModel(parent, repository)
{
    setModelType(InspectorModelType::TYPE_LYRICS);
    setTitle(qtrc("inspector", "Lyrics"));
    setIcon(ui::IconCode::Code::LYRICS);
    createProperties();
}

void LyricsSettingsModel::createProperties()
{
    m_verse = buildPropertyItem(mu::engraving::Pid::VERSE);
    m_staffshift = buildPropertyItem(mu::engraving::Pid::LYRICS_STAFF_SHIFT);
}

void LyricsSettingsModel::requestElements()
{
    m_elementList = m_repository->findElementsByType(mu::engraving::ElementType::LYRICS);
}

void LyricsSettingsModel::loadProperties()
{
    loadPropertyItem(m_verse);
    loadPropertyItem(m_staffshift);
}

void LyricsSettingsModel::resetProperties()
{
    m_verse->resetToDefault();
    m_staffshift->resetToDefault();
}

PropertyItem* LyricsSettingsModel::verse() const
{
    return m_verse;
}

PropertyItem* LyricsSettingsModel::LYRICS_STAFF_SHIFT() const
{
    return m_staffshift;
}
