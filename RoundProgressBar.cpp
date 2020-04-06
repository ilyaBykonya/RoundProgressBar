#include "RoundProgressBar.h"

RoundProgressBar::RoundProgressBar(QWidget *parent)
    :QWidget{ parent },
     m_configuration{ RoundConfiguration::PieRound },
     m_progress{ 0 },
     m_maximum{ 100 },
     m_minimum{ 0 },
     m_countOfNeedless{ 30 },
     m_centralEllipseColor{ Qt::GlobalColor::black },
     m_progressTextColor{ Qt::GlobalColor::white },
     m_onElementsColor{ Qt::GlobalColor::green },
     m_offElementsColor{ Qt::GlobalColor::red }

    {
    }

void RoundProgressBar::paintEvent(QPaintEvent*)
{
    switch (this->m_configuration)
    {
        case RoundConfiguration::PieRound: drawPieRound(); break;
        case RoundConfiguration::HedgehogRound: drawHedgehogRound(); break;
    }
}
void RoundProgressBar::drawPieRound()
{
    QPainter painter;
    painter.begin(this);
        painter.setBrush(QBrush(m_offElementsColor));
        painter.drawEllipse(this->rect());

        painter.setBrush(QBrush(m_onElementsColor));
        qreal difference = m_maximum - m_minimum;
        qreal percent = 360.0 / difference;
        qreal angle = percent * m_progress * 16.0;
        painter.drawPie(this->rect(), 90 * 16, angle);

        painter.setBrush(QBrush(m_centralEllipseColor));
        painter.drawEllipse(this->width() * 0.15, this->height() * 0.15, this->width() * 0.7, this->height() * 0.7);

        painter.setPen(QPen(m_progressTextColor, 2));
        QString text = QString::number(static_cast<qreal>(m_progress) / (m_maximum - m_minimum) * 100.0) + "%";
        painter.drawText(this->rect(),Qt::AlignmentFlag::AlignCenter, text);
    painter.end();
}
void RoundProgressBar::drawHedgehogRound()
{
    QPainter painter;
    painter.begin(this);
        painter.setBrush(QBrush(m_centralEllipseColor));
        painter.drawEllipse(this->width() * 0.1, this->height() * 0.1, this->width() * 0.8, this->height() * 0.8);

        painter.setPen(QPen(m_progressTextColor, 2));
        QString text = QString::number(static_cast<qreal>(m_progress) / (m_maximum - m_minimum) * 100.0) + "%";
        painter.drawText(this->rect(),Qt::AlignmentFlag::AlignCenter, text);

        painter.setPen(QPen(m_onElementsColor, 2));

        int OnLines = static_cast<qreal>(m_progress - m_minimum) / (m_maximum - m_minimum) * m_countOfNeedless;
        for(int i = 0; i < m_countOfNeedless; ++i)
        {
            if(i == OnLines)
                painter.setPen(QPen(m_offElementsColor, 2));

            qreal angle = ::qDegreesToRadians(-360.0 * i / m_countOfNeedless - 90);
            QPoint p1(this->width() / 2 + this->width() * 0.45 * cos(angle), this->height() / 2 + this->height() * 0.45 * sin(angle));
            QPoint p2(this->width() / 2 + this->width() * 0.5 * cos(angle), this->height() / 2 + this->height() * 0.5 * sin(angle));
            painter.drawLine(p1, p2);


        }
    painter.end();
}


int RoundProgressBar::countOfDashs() const { return m_countOfNeedless; }
void RoundProgressBar::setCountOfDash(int dash)
{
    m_countOfNeedless = dash < 1 ? 1 : dash;
    this->repaint();
}


int RoundProgressBar::value() const { return m_progress; }
void RoundProgressBar::setValue(int num)
{
    m_progress = (num < m_minimum ? m_minimum : num > m_maximum ? m_maximum : num);
    emit valueChanged(m_progress);

    if(m_progress == m_maximum)
        emit fullFilling();

    this->repaint();
}
void RoundProgressBar::setPercent(qreal percent)
{
    if(percent > 100.0) {
        percent = 100.0;
    } else if(percent < 0.0) {
        percent = 0.0;
    }

    qreal newValue = percent / 100.0;
    int difference = m_maximum - m_minimum;
    this->setValue(newValue * difference + m_minimum);
}



QSize RoundProgressBar::sizeHint() const
{
    return QSize(40, 40);
}



void RoundProgressBar::setRange(int min, int max)
{
    if(min < max) {
        m_maximum = max;
        m_minimum = min;
    } else if(min > max) {
        m_maximum = min;
        m_minimum = max;
    }

    this->setValue(this->value());
}
void RoundProgressBar::setMinimum(int min)
{
    if(min >= m_maximum)
        return;

    m_minimum = min;
    this->setValue(this->value());
}
void RoundProgressBar::setMaximum(int max)
{
    if(max <= m_minimum)
        return;

    m_maximum = max;
    this->setValue(this->value());
}
QPair<int, int> RoundProgressBar::range() const { return QPair<int, int>(m_minimum, m_maximum); }
int RoundProgressBar::maximum() const { return m_maximum; }
int RoundProgressBar::minimum() const { return m_minimum; }



void RoundProgressBar::doPieRoundConfiguration()
{
    m_configuration = RoundConfiguration::PieRound;
}
void RoundProgressBar::doHedgehogRoundConfiguration(int countOfdash)
{
    m_configuration = RoundConfiguration::HedgehogRound;
    m_countOfNeedless = countOfdash;
}
RoundProgressBar::RoundConfiguration RoundProgressBar::roundConfiguration() const { return m_configuration; }



void RoundProgressBar::setCentralEllipseColor(Qt::GlobalColor color){ m_centralEllipseColor = color; }
void RoundProgressBar::setProgressTextColor(Qt::GlobalColor color){ m_progressTextColor = color; }
void RoundProgressBar::setOnElementsColor(Qt::GlobalColor color){ m_onElementsColor = color; }
void RoundProgressBar::setOffElementsColor(Qt::GlobalColor color){ m_offElementsColor = color; }
QColor RoundProgressBar::centralEllipseColor() const { return m_centralEllipseColor; }
QColor RoundProgressBar::progressTextColor() const { return m_progressTextColor; }
QColor RoundProgressBar::onElementsColor() const { return m_onElementsColor; }
QColor RoundProgressBar::offElementsColor() const { return m_offElementsColor; }
