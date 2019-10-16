#ifndef NUMERIC_H
#define NUMERIC_H


namespace Ms {


class numeric
      {

      qreal _relativeSize;
public:
      qreal textWidth(const QFont font, const QString string) const;
      qreal textHeigth(const QFont font, const QString string) const;

      void set_relativeSize(qreal size){_relativeSize = size;}

      qreal get_relativeSize() {return _relativeSize;}
      QRectF bbox(QFont font, QPointF pos, QString string);
      QString shapString() {return "♯";}
      QString flatString() {return "♭";}

      void drawShap(QPainter* painter, QPointF pos, QFont font) const;
      void drawFlat(QPainter* painter, QPointF pos, QFont font) const;
      };
}
#endif // NUMERIC_H
