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

#include "hook.h"
#include "draw/fontmetrics.h"
#include "draw/types/font.h"

#include "chord.h"
#include "score.h"
#include "staff.h"

#include "log.h"

using namespace mu;
using namespace mu::engraving;

Hook::Hook(Chord* parent)
    : Symbol(ElementType::HOOK, parent, ElementFlag::NOTHING)
{
    setZ(int(type()) * 100);
}

EngravingItem* Hook::elementBase() const
{
    return parentItem();
}

void Hook::setHookType(int i)
{
    bool straight = score()->styleB(Sid::useStraightNoteFlags);
    _hookType = i;
    setSym(symIdForHookIndex(i, straight));
}

void Hook::layout()
{
    if (staff() && staff()->isCipherStaff(tick())) {

        _cipherLineThick = _cipherHigth * score()->styleD(Sid::cipherThickLine);
        _cipherLineSpace = _cipherHigth * (score()->styleD(Sid::cipherDistanceBetweenLines) * -1);
        _cipherHigthLine = _cipherHigth * score()->styleD(Sid::cipherHeightDisplacement) - _cipherHigth - _cipherHigth * score()->styleD(Sid::cipherHeigthLine);
        double linienlaenge = _cipherLineWidht * score()->styleD(Sid::cipherWideLine);
        RectF hookbox = RectF(score()->styleD(Sid::cipherOffsetLine) + ((_cipherLineWidht - linienlaenge) / 2),
            _cipherHigthLine + ((qAbs(_hookType) - 1) * _cipherLineSpace) - _cipherLineThick, linienlaenge,
            (_cipherHigthLine + ((qAbs(_hookType) - 1) * _cipherLineSpace) - _cipherLineThick) * -1 - _cipherHigthLine * -1);
        setbbox(hookbox);

    }
    else {
        setbbox(symBbox(_sym));
    }
}

void Hook::draw(mu::draw::Painter* painter) const
{
    TRACE_OBJ_DRAW;
    if (staff() && staff()->isCipherStaff(tick())) {
        painter->setPen(mu::draw::Pen(curColor(), _cipherLineThick));
        for (int i = 0; i < qAbs(_hookType); ++i) {

            painter->drawLine(LineF(score()->styleD(Sid::cipherOffsetLine) + (_cipherLineWidht / 2 - (_cipherLineWidht * score()->styleD(Sid::cipherWideLine)) / 2),
                _cipherHigthLine + (i * _cipherLineSpace),
                score()->styleD(Sid::cipherOffsetLine) + (_cipherLineWidht / 2 + (_cipherLineWidht * score()->styleD(Sid::cipherWideLine)) / 2),
                _cipherHigthLine + (i * _cipherLineSpace)));
        }
        return;
    }
    // hide if belonging to the second chord of a cross-measure pair
    if (chord() && chord()->crossMeasure() == CrossMeasure::SECOND) {
        return;
    }

    painter->setPen(curColor());
    drawSymbol(_sym, painter);
}

mu::PointF Hook::smuflAnchor() const
{
    return symSmuflAnchor(_sym, chord()->up() ? SmuflAnchorId::stemUpNW : SmuflAnchorId::stemDownSW);
}

SymId Hook::symIdForHookIndex(int index, bool straight)
{
    switch (index) {
    case 0:
        return SymId::noSym;
    case 1:
        return straight ? SymId::flag8thUpStraight : SymId::flag8thUp;
    case 2:
        return straight ? SymId::flag16thUpStraight : SymId::flag16thUp;
    case 3:
        return straight ? SymId::flag32ndUpStraight : SymId::flag32ndUp;
    case 4:
        return straight ? SymId::flag64thUpStraight : SymId::flag64thUp;
    case 5:
        return straight ? SymId::flag128thUpStraight : SymId::flag128thUp;
    case 6:
        return straight ? SymId::flag256thUpStraight : SymId::flag256thUp;
    case 7:
        return straight ? SymId::flag512thUpStraight : SymId::flag512thUp;
    case 8:
        return straight ? SymId::flag1024thUpStraight : SymId::flag1024thUp;

    case -1:
        return straight ? SymId::flag8thDownStraight : SymId::flag8thDown;
    case -2:
        return straight ? SymId::flag16thDownStraight : SymId::flag16thDown;
    case -3:
        return straight ? SymId::flag32ndDownStraight : SymId::flag32ndDown;
    case -4:
        return straight ? SymId::flag64thDownStraight : SymId::flag64thDown;
    case -5:
        return straight ? SymId::flag128thDownStraight : SymId::flag128thDown;
    case -6:
        return straight ? SymId::flag256thDownStraight : SymId::flag256thDown;
    case -7:
        return straight ? SymId::flag512thDownStraight : SymId::flag512thDown;
    case -8:
        return straight ? SymId::flag1024thDownStraight : SymId::flag1024thDown;
    default:
        LOGE() << "No hook/flag for hook index: " << index;
        break;
    }

    return SymId::noSym;
}
