#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QRegularExpression>

enum class Typography {
    Title1,
    Title2,
    Title3,
    Subtitle1,
    Subtitle2,
    Subtitle2Stronger,
    Caption1,
    Caption1Strong,
    Caption1Stronger,
    Caption2,
    Caption2Strong,
    Body1,
    Body1Strong,
    Body1Stronger,
    Body2,
    Body2Strong,
    Body2Stronger
};

enum class Priority {
    Primary,
    Secondary,
    Tertiary
};

enum class SizeScale {
    Small,
    Medium,
    Large
};

enum class Condition {
    Normal,
    Error
};

class IPropertyInterface {
public:
    void setTypography(const Typography& typography);
    void setPriority(const Priority& priority);
    void setSizeScale(const SizeScale& scale);
    void setCondition(const Condition& condition);

    virtual void setPropertyValue(const QString& name, const QVariant& value) = 0;
};

class Label : public QLabel, public IPropertyInterface
{
    Q_OBJECT
public:
    Label(QWidget* parent = nullptr);
    Label(const QString& text, QWidget* parent = nullptr);

    void setPriority(const Priority& priority) = delete;
    void setSizeScale(const SizeScale& scale) = delete;

    void setPropertyValue(const QString& name, const QVariant& value) override;
};

class PushButton : public QPushButton, public IPropertyInterface
{
    Q_OBJECT
public:
    PushButton(QWidget* parent = nullptr);
    PushButton(const QString& text, QWidget* parent = nullptr);

    void setTypography(const Typography& typography) = delete;
    void setCondition(const Condition& condition) = delete;

    void setPropertyValue(const QString& name, const QVariant& value) override;
};

class SpinBox : public QSpinBox, public IPropertyInterface
{
    Q_OBJECT
public:
    SpinBox(QWidget* parent = nullptr);

    void setTypography(const Typography& typography) = delete;
    void setPriority(const Priority& priority) = delete;
    void setCondition(const Condition& condition) = delete;

    void setPropertyValue(const QString& name, const QVariant& value) override;
};

class DoubleSpinBox : public QDoubleSpinBox, public IPropertyInterface
{
    Q_OBJECT
public:
    DoubleSpinBox(QWidget* parent = nullptr);

    void setTypography(const Typography& typography) = delete;
    void setPriority(const Priority& priority) = delete;
    void setCondition(const Condition& condition) = delete;

    void setPropertyValue(const QString& name, const QVariant& value) override;
};

class LineEdit : public QLineEdit, public IPropertyInterface
{
    Q_OBJECT
public:
    LineEdit(QWidget* parent = nullptr);

    void setTypography(const Typography& typography) = delete;
    void setPriority(const Priority& priority) = delete;

    void setPropertyValue(const QString& name, const QVariant& value) override;
};

class LineEditExt : public QWidget
{
    Q_OBJECT
public:
    LineEditExt(QWidget* parent = nullptr);

    LineEdit* lineEdit();

    void setRegExp(const QRegularExpression& regExp);
    bool isValid() const;

signals:
    void validEditingFinished(const QString& text);

private:
    void updateState();

private:
    LineEdit* m_lineEdit{nullptr};
    Label* m_errorLabel{nullptr};
    Label* m_iconLabel{nullptr};
    QRegularExpression m_regExp;
};

#endif // CUSTOMWIDGETS_H
