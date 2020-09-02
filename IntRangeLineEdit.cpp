#include "IntRangeLineEdit.h"

IntRangeLineEdit ::IntRangeLineEdit(QWidget *parent, IntRangeLineEditFocusType focusType,
                                    QString id, int defaultValue, int lower, int upper) :
    QLineEdit(parent)
{
    this->lastValue = defaultValue;
    this->setText(QString::number(defaultValue));
    this->lower = lower;
    this->upper = upper;
    this->focusType = focusType;
    this->id = new QString(id);
    this->setValidator(new QIntValidator(lower, upper, this));
}

IntRangeLineEdit ::~IntRangeLineEdit()
{
    delete this->id;
}

QString *IntRangeLineEdit::getId()
{
    return this->id;
}

QString IntRangeLineEdit::getValidationError()
{
    if (!this->hasAcceptableInput()) {
        if (cachedError == nullptr) {
            QString tempCachedError = QString("%1: %2 (%3: %4)");

            QString range
                = QString::number(this->lower).append("-").append(QString::number(this->upper));

            tempCachedError
                = tempCachedError.arg(tr("Number is invalid"), "#", tr("Valid range is"),
                                      range);
            this->cachedError = new QString(tempCachedError.replace('#', "%1"));
        }
        return this->cachedError->arg(this->text());
    }
    return nullptr;
}

int IntRangeLineEdit::getLastValue()
{
    return this->lastValue;
}

void IntRangeLineEdit::setNewValue(int newValue)
{
    this->lastValue = newValue;
}

int IntRangeLineEdit::getIntValue()
{
    bool ok;
    int n = this->text().toInt(&ok);
    return (ok == true) ? n : -1;
}

unsigned long IntRangeLineEdit::getLongValue()
{
    return static_cast<unsigned long>(this->text().toLong());
}

void IntRangeLineEdit ::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    if (this->focusType == IntRangeLineEditFocusType::In
        || this->focusType == IntRangeLineEditFocusType::Both)
        emit(focussed(this, true, this->getIntValue()));
}

void IntRangeLineEdit ::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    if (this->focusType == IntRangeLineEditFocusType::Out
        || this->focusType == IntRangeLineEditFocusType::Both)
        emit(focussed(this, false, this->getIntValue()));
}
