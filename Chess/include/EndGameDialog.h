#ifndef ENDGAMEDIALOG_H
#define ENDGAMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class EndGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndGameDialog(QWidget *parent = nullptr);

    void setWinner(const QString &winner);

    void setDraw();

private:
    QLabel *messageLabel;  ///< Label to display the end game message
    QPushButton *okButton; ///< Button to close the dialog
};

#endif