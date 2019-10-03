#ifndef NUMERIC_H
#define NUMERIC_H


namespace Ms {


class numeric
      {

      qreal _relativeSize;
public:
      qreal textWidth(const QFont font, const QString string) const;

      void set_relativeSize(qreal size){_relativeSize = size;}

      qreal get_relativeSize() {return _relativeSize;}
      };
}
#endif // NUMERIC_H
