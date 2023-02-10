#include "cipher.h"
#include "mscore.h"
#include "draw/types/brush.h"
#include <draw/types/font.h>
#include <draw/painter.h>
#include <notation/notationtypes.h>
#include "accidental.h"


namespace mu::engraving {
    //---------------------------------------------------------
    //   textWidth
    //---------------------------------------------------------

    qreal cipher::textWidth(const mu::draw::Font font, const String string) const
    {
        qreal val;
        mu::draw::FontMetrics fm(font);
        val = fm.width(string);
        return val;
    }
    cipher::cipher()
    {
        set_Debugg(RectF());
    }
    qreal cipher::textHeigth(const mu::draw::Font font, const String string) const
    {
        qreal val;
        mu::draw::FontMetrics fm(font);
        RectF pos = fm.tightBoundingRect(string);
        val = pos.height();
        return val;
    }
    RectF cipher::bbox(mu::draw::Font font, PointF pos, String string)
    {
        mu::draw::FontMetrics fm(font);
        return fm.tightBoundingRect(string).translated(pos);
    }
    void cipher::drawShap(mu::draw::Painter* painter, PointF pos, mu::draw::Font font) const
    {
        mu::draw::Font fontold = painter->font();
        painter->setFont(font);
        painter->drawText(pos, (String)"♯");
        painter->setFont(fontold);
    }
    void cipher::drawFlat(mu::draw::Painter* painter, PointF pos, mu::draw::Font font) const
    {
        mu::draw::Font fontold = painter->font();
        painter->setFont(font);
        painter->drawText(pos, (String)"♭");
        painter->setFont(fontold);
    }

    //---------------------------------------------------------
    //   drawRectF
    //---------------------------------------------------------

    void cipher::drawRectF(mu::draw::Painter* painter, RectF rectf, mu::draw::Color coler) const
    {

        painter->setPen(mu::draw::Pen(coler, 1.0));
        painter->drawLine(LineF(rectf.x(), rectf.y(), rectf.x(), rectf.y()+ rectf.height()));
        painter->drawLine(LineF(rectf.x(), rectf.y(), rectf.x() + rectf.width(), rectf.y()));
        painter->drawLine(LineF(rectf.x() + rectf.width(), rectf.y() + rectf.height(), rectf.x() + rectf.width(), rectf.y()));
        painter->drawLine(LineF(rectf.x() + rectf.width(), rectf.y() + rectf.height(), rectf.x(), rectf.y() + rectf.height()));
    }

    //---------------------------------------------------------
    //   drawDebugg
    //---------------------------------------------------------

    void cipher::drawDebugg(mu::draw::Painter* painter) const
    {
        drawRectF(painter, _debugg, mu::draw::Color(0, 255, 0));
    }
    //---------------------------------------------------------
    //   get_cipherTrans
    //---------------------------------------------------------
    int cipher::get_cipherTrans(Key key) const {
        switch (key) {
        case Key::C_B:  return 1;
        case Key::G_B:  return -6;
        case Key::D_B:  return -1;
        case Key::A_B:  return 4;
        case Key::E_B:  return -3;
        case Key::B_B:  return 2;
        case Key::F:  return -5;
        case Key::C:  return 0;
        case Key::G:  return 5;
        case Key::D:  return -2;
        case Key::A:  return 3;
        case Key::E:  return -4;
        case Key::B:  return 1;
        case Key::F_S:  return -6;
        case Key::C_S:  return 1;
        default:
            return 0;
            break;
        }
    }
}
