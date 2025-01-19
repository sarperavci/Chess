#include "EndGameDialog.h"

EndGameDialog::EndGameDialog(QWidget *parent)
    : QDialog(parent), messageLabel(new QLabel(this)), okButton(new QPushButton("OK", this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    layout->addWidget(messageLabel);
    layout->addWidget(okButton);
    setLayout(layout);
    setFixedSize(400, 200);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
}

void EndGameDialog::setWinner(const QString &winner)
{
    messageLabel->setText(QString("Checkmate! %1 wins!").arg(winner));
}

void EndGameDialog::setDraw()
{
    messageLabel->setText("Draw!");
}