#include "Views/CustomWidgets.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyle>

// IPropertyInterface
void IPropertyInterface::setTypography(const Typography &typography)
{
    switch(typography)
    {
    case Typography::Title1:
        setPropertyValue("typography", "t1");
        break;
    case Typography::Title2:
        setPropertyValue("typography", "t2");
        break;
    case Typography::Title3:
        setPropertyValue("typography", "t3");
        break;
    case Typography::Subtitle1:
        setPropertyValue("typography", "s1");
        break;
    case Typography::Subtitle2:
        setPropertyValue("typography", "s2");
        break;
    case Typography::Subtitle2Stronger:
        setPropertyValue("typography", "s2sr");
        break;
    case Typography::Caption1:
        setPropertyValue("typography", "c1");
        break;
    case Typography::Caption1Strong:
        setPropertyValue("typography", "c1s");
        break;
    case Typography::Caption1Stronger:
        setPropertyValue("typography", "c1sr");
        break;
    case Typography::Caption2:
        setPropertyValue("typography", "c2");
        break;
    case Typography::Caption2Strong:
        setPropertyValue("typography", "c2s");
        break;
    case Typography::Body1:
        setPropertyValue("typography", "b1");
        break;
    case Typography::Body1Strong:
        setPropertyValue("typography", "b1s");
        break;
    case Typography::Body1Stronger:
        setPropertyValue("typography", "b1sr");
        break;
    case Typography::Body2:
        setPropertyValue("typography", "b2");
        break;
    case Typography::Body2Strong:
        setPropertyValue("typography", "b2s");
        break;
    case Typography::Body2Stronger:
        setPropertyValue("typography", "b2sr");
        break;
    }
}

void IPropertyInterface::setPriority(const Priority &priority)
{
    switch(priority)
    {
    case Priority::Primary:
        setPropertyValue("priority", "primary");
        break;
    case Priority::Secondary:
        setPropertyValue("priority", "secondary");
        break;
    case Priority::Tertiary:
        setPropertyValue("priority", "tertiary");
        break;
    }
}

void IPropertyInterface::setSizeScale(const SizeScale &scale)
{
    switch(scale)
    {
    case SizeScale::Small:
        setPropertyValue("scale", "s");
        break;
    case SizeScale::Medium:
        setPropertyValue("scale", "m");
        break;
    case SizeScale::Large:
        setPropertyValue("scale", "l");
        break;
    }
}

void IPropertyInterface::setCondition(const Condition &condition)
{
    switch(condition)
    {
    case Condition::Error:
        setPropertyValue("condition", "error");
        break;
    case Condition::Normal:
        setPropertyValue("condition", "normal");
        break;
    }
}

// Label
Label::Label(QWidget *parent)
    : QLabel(parent)
{}

Label::Label(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{}

void Label::setPropertyValue(const QString &name, const QVariant &value)
{
    setProperty(name.toStdString().c_str(), value);
}

// PushButton
PushButton::PushButton(QWidget *parent)
    : QPushButton(parent)
{}

PushButton::PushButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{}

void PushButton::setPropertyValue(const QString &name, const QVariant &value)
{
    setProperty(name.toStdString().c_str(), value);
}

// SpinBox
SpinBox::SpinBox(QWidget *parent)
    : QSpinBox(parent)
{}

void SpinBox::setPropertyValue(const QString &name, const QVariant &value)
{
    setProperty(name.toStdString().c_str(), value);
}

// DoubleSpinBox
DoubleSpinBox::DoubleSpinBox(QWidget *parent)
    : QDoubleSpinBox(parent)
{}

void DoubleSpinBox::setPropertyValue(const QString &name, const QVariant &value)
{
    setProperty(name.toStdString().c_str(), value);
}

// LineEdit
LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
{}

void LineEdit::setPropertyValue(const QString &name, const QVariant &value)
{
    setProperty(name.toStdString().c_str(), value);
}

// LineEditExt
LineEditExt::LineEditExt(QWidget* parent)
    : QWidget(parent)
{
    m_regExp = QRegularExpression("^[a-zA-Z0-9_]+$");
    m_lineEdit = new LineEdit(this);

    m_iconLabel = new Label(this);
    m_iconLabel->setPixmap(QPixmap(":/Resources/Icons/error.png"));
    m_iconLabel->setFixedWidth(12);
    m_iconLabel->hide();

    m_errorLabel = new Label(this);
    m_errorLabel->setCondition(Condition::Error);
    m_errorLabel->setTypography(Typography::Body1);
    m_errorLabel->setAlignment(Qt::AlignVCenter);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    auto hlayout = new QHBoxLayout();
    hlayout->addWidget(m_iconLabel);
    hlayout->addWidget(m_errorLabel);
    hlayout->setContentsMargins(0, 6, 0, 0);
    hlayout->setSpacing(2);

    auto vlayout = new QVBoxLayout(this);
    vlayout->addWidget(m_lineEdit);
    vlayout->addLayout(hlayout);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setSpacing(0);

    connect(m_lineEdit, &QLineEdit::textEdited, this, &LineEditExt::updateState);
    connect(m_lineEdit, &QLineEdit::editingFinished, this, [&](){
        if (isValid())
        {
            emit validEditingFinished(m_lineEdit->text());
        }
    });
}

LineEdit *LineEditExt::lineEdit()
{
    return m_lineEdit;
}

void LineEditExt::setRegExp(const QRegularExpression &regExp)
{
    if (m_regExp != regExp)
    {
        m_regExp = regExp;
        updateState();
    }
}

bool LineEditExt::isValid() const
{
    return m_regExp.match(m_lineEdit->text()).hasMatch();
}

void LineEditExt::updateState()
{
    auto isMatch = isValid();
    auto condition = isMatch ? Condition::Normal
                             : Condition::Error;
    m_lineEdit->setCondition(condition);
    m_lineEdit->style()->unpolish(m_lineEdit);
    m_lineEdit->style()->polish(m_lineEdit);
    m_errorLabel->setText(isMatch ? "" : tr("Invalid input"));
    m_iconLabel->setVisible(!isMatch);
}
