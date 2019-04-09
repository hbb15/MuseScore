#include "numeric.h"
#include "mscore.h"


namespace Ms {
//---------------------------------------------------------
//   textWidth
//---------------------------------------------------------

qreal numeric::textWidth(const QFont font, const QString string) const
      {
      qreal val;
      QFontMetricsF fm(font, MScore::paintDevice());
      val  = fm.width(string);
      return val;
      }

}
