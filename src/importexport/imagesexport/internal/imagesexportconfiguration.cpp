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
#include "imagesexportconfiguration.h"

#include "settings.h"

#include "engraving/dom/mscore.h"

using namespace mu::framework;
using namespace mu::iex::imagesexport;

static const Settings::Key EXPORT_PDF_DPI_RESOLUTION_KEY("iex_imagesexport", "export/pdf/dpi");
static const Settings::Key EXPORT_PNG_DPI_RESOLUTION_KEY("iex_imagesexport", "export/png/resolution");
static const Settings::Key EXPORT_PNG_USE_TRANSPARENCY_KEY("iex_imagesexport", "export/png/useTransparency");

void ImagesExportConfiguration::init()
{
    settings()->setDefaultValue(EXPORT_PNG_DPI_RESOLUTION_KEY, Val(mu::engraving::DPI));
    settings()->setDefaultValue(EXPORT_PDF_DPI_RESOLUTION_KEY, Val(mu::engraving::DPI));
    settings()->setDefaultValue(EXPORT_PNG_USE_TRANSPARENCY_KEY, Val(false));
}

int ImagesExportConfiguration::exportPdfDpiResolution() const
{
    return settings()->value(EXPORT_PDF_DPI_RESOLUTION_KEY).toInt();
}

void ImagesExportConfiguration::setExportPdfDpiResolution(int dpi)
{
    settings()->setSharedValue(EXPORT_PDF_DPI_RESOLUTION_KEY, Val(dpi));
}

float ImagesExportConfiguration::exportPngDpiResolution() const
{
    if (m_customExportPngDpiOverride) {
        return m_customExportPngDpiOverride.value();
    }

    return settings()->value(EXPORT_PNG_DPI_RESOLUTION_KEY).toFloat();
}

void ImagesExportConfiguration::setExportPngDpiResolution(float dpi)
{
    settings()->setSharedValue(EXPORT_PNG_DPI_RESOLUTION_KEY, Val(dpi));
}

void ImagesExportConfiguration::setExportPngDpiResolutionOverride(std::optional<float> dpi)
{
    m_customExportPngDpiOverride = dpi;
}

bool ImagesExportConfiguration::exportPngWithTransparentBackground() const
{
    return settings()->value(EXPORT_PNG_USE_TRANSPARENCY_KEY).toBool();
}

void ImagesExportConfiguration::setExportPngWithTransparentBackground(bool transparent)
{
    settings()->setSharedValue(EXPORT_PNG_USE_TRANSPARENCY_KEY, Val(transparent));
}

int ImagesExportConfiguration::trimMarginPixelSize() const
{
    return m_trimMarginPixelSize ? m_trimMarginPixelSize.value() : -1;
}

void ImagesExportConfiguration::setTrimMarginPixelSize(std::optional<int> pixelSize)
{
    m_trimMarginPixelSize = pixelSize;
}
