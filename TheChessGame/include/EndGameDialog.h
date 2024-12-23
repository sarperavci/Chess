#ifndef ENDGAMEDIALOG_H
#define ENDGAMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

/**
 * @brief The EndGameDialog class represents a dialog that is shown at the end of the game.
 */
class EndGameDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the EndGameDialog class.
     * @param parent The parent widget.
     */
    explicit EndGameDialog(QWidget *parent = nullptr);

    /**
     * @brief Set the winner message in the dialog.
     * @param winner The name of the winner.
     */
    void setWinner(const QString &winner);

    /**
     * @brief Set the draw message in the dialog.
     */
    void setDraw();

private:
    QLabel *messageLabel; ///< Label to display the end game message
    QPushButton *okButton; ///< Button to close the dialog
};

#endif