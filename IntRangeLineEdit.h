#ifndef INTRANGELINEEDIT_H
#define INTRANGELINEEDIT_H

#include <QString>
#include <QFocusEvent>
#include <QIntValidator>
#include <QWidget>
#include <QLineEdit>

enum IntRangeLineEditFocusType {
    Out,
    In,
    Both
};

class IntRangeLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    IntRangeLineEdit (QWidget *parent = 0,
                      IntRangeLineEditFocusType focusType = IntRangeLineEditFocusType::Out,
                      QString id = nullptr, int defaultValue = 0, int lower = 0, int upper = 1);
    ~IntRangeLineEdit ();

    QString getValidationError();
    int getLastValue();
    void setNewValue(int newValue);
    QString *getId();
    int getIntValue();
    unsigned long getLongValue();

signals:
    void focussed(IntRangeLineEdit *le, bool hasFocus, int value);

protected:
    virtual void focusInEvent(QFocusEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);

private:
    int lower, upper, lastValue;
    QString *id;
    QString *cachedError = nullptr;
    IntRangeLineEditFocusType focusType;
};
#endif // INTRANGELINEEDIT_H
