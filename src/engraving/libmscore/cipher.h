#ifndef CIPHER_H
#define CIPHER_H


#include "engravingitem.h"

namespace mu::engraving {


    class cipher
    {

        qreal _relativeSize;
        mu::draw::Font _cipherFont;
        RectF _debugg;
    public:
        cipher();
        qreal textWidth(const mu::draw::Font font, const String string) const;
        qreal textHeigth(const mu::draw::Font font, const String string) const;

        void set_relativeSize(qreal size) { _relativeSize = size; }
        void set_CipherFont(mu::draw::Font font) { _cipherFont = font; }
        void set_Debugg(RectF rectf) {
            _debugg = rectf; }

        qreal get_relativeSize() { return _relativeSize; }
        RectF bbox(mu::draw::Font font, PointF pos, String string);
        String shapString() { return (String)"♯"; }
        String flatString() { return (String)"♭"; }
        mu::draw::Font getCipherFont() const { return _cipherFont; }


        void drawShap(mu::draw::Painter* painter, PointF pos, mu::draw::Font font) const;
        void drawFlat(mu::draw::Painter* painter, PointF pos, mu::draw::Font font) const;
        void drawRectF(mu::draw::Painter* painter, RectF rectf, mu::draw::Color coler) const;
        void drawDebugg(mu::draw::Painter* painter) const;
        int get_cipherTrans(Key key) const;
        bool debug() const { return true; }

    };
}
#endif // CIPHER_H
