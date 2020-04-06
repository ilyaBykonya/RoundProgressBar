#ifndef ROUNDPROGRESSBAR_H
#define ROUNDPROGRESSBAR_H

#include <QtWidgets>

class RoundProgressBar : public QWidget
{
    Q_OBJECT
public:
    enum RoundConfiguration
    {
        PieRound,
        HedgehogRound
    };
protected:
    RoundConfiguration m_configuration;
    int m_progress;


    int m_maximum;
    int m_minimum;


    int m_countOfNeedless;//Для режима HedgehogRound(ёж)


    QColor m_centralEllipseColor;
    QColor m_progressTextColor;
    QColor m_onElementsColor;
    QColor m_offElementsColor;



    virtual void paintEvent(QPaintEvent*) override;
    void drawPieRound();
    void drawHedgehogRound();
public:
    explicit RoundProgressBar(QWidget *parent = nullptr);

    virtual QSize sizeHint() const override;

    QPair<int, int> range() const;
    int maximum() const;
    int minimum() const;

    int value() const;
    RoundConfiguration roundConfiguration() const;
    int countOfDashs() const;

    QColor centralEllipseColor() const;
    QColor progressTextColor() const;
    QColor onElementsColor() const;
    QColor offElementsColor() const;
public slots:
    void setValue(int);
    void setCountOfDash(int);
    void setPercent(qreal);

    void setRange(int, int);
    void setMinimum(int);
    void setMaximum(int);

    void doPieRoundConfiguration();
    void doHedgehogRoundConfiguration(int countOfdash = 30);

    void setCentralEllipseColor(Qt::GlobalColor);
    void setProgressTextColor(Qt::GlobalColor);
    void setOnElementsColor(Qt::GlobalColor);
    void setOffElementsColor(Qt::GlobalColor);

signals:
    void valueChanged(int);
    void fullFilling();
};

#endif // ROUNDPROGRESSBAR_H
