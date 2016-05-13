////////////////////////////////////////////////////////////
///     Cat Fortman
///     QT
///     Hangman project
///
///////////////////////////////////////////////////////////

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Model/hangmanclass.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <map>
#include <QMessageBox>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _imageFor({ {Picture::ONE, "border-image:url(:/route/Media/images/gallows0.png)"}, // all the pictures and URLS
    {Picture::TWO, "border-image:url(:/route/Media/images/gallows1.png)"},
    {Picture::THREE, "border-image:url(:/route/Media/images/gallows2.png)"},
    {Picture::FOUR, "border-image:url(:/route/Media/images/gallows3.png)"},
    {Picture::FIVE, "border-image:url(:/route/Media/images/gallows4.png)"},
    {Picture::SIX, "border-image:url(:/route/Media/images/gallows5.png)"},
    {Picture::SEVEN,"border-image:url(:/route/Media/images/gallows6.png)"}})

{
    ui->setupUi(this);
    _game = std::unique_ptr<hangmanClass>(new hangmanClass());

    auto vlMain = new QVBoxLayout(ui->centralWidget);
    auto hlTop = new QHBoxLayout(); // holds picture and grid layout
    auto glLetters = new QGridLayout(); // letters
    auto hlPhrase = new QHBoxLayout(); // holds phrase
    auto hlNewBtn = new QHBoxLayout(); // holds new phrase button

    lblPicture = new QLabel();                             // label for picture
    lblPicture->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lblPicture->setMaximumSize(300,300);
    lblPicture->setMinimumSize(300,300);

    for(char c= 'a'; c <= 'z'; ++c)                                  // all the letter buttons
    {
        auto btn = new QPushButton();
        btn->setMaximumSize(20,20);
        btn->setMaximumSize(20,20);
        btn->setText(QString(c));

        int idx = c - 'a';

        glLetters->addWidget(btn, idx / 6, idx % 6);// adds to grid layout

        connect(btn, &QPushButton::clicked, this, &MainWindow::onLetterClicked);
        letters.push_back(btn);
    }

    hlTop->addWidget(lblPicture); // adds the picture to the horizontal layout

    QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed); // spacer between picture and letters
    hlTop->addSpacerItem(spacer); // adds the spacer to top layout

    hlTop->addLayout(glLetters);  // adds the letters in grid to horizontal

    vlMain->addLayout(hlTop); // adds the top layout to the main vertical layout

    QSpacerItem *spacer1 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed); // spacer on right of phrase

    lblPhrase = new QLabel;  // new label for the hidden phrase
    lblPhrase->setMaximumSize(400,25);
    lblPhrase->setMinimumSize(400,25);
    lblPhrase->setFrameStyle(QFrame::NoFrame);

    hlPhrase->addWidget(lblPhrase); // add the phrase to the hl
    hlPhrase->addSpacerItem(spacer1);// phrase layout adds spacer

    vlMain->addLayout(hlPhrase); // add phrase layout to the main layout

    QSpacerItem *spacer2 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed); // new spacer for left of new button

    auto btnNewPhrase= new QPushButton(); // create button for new phrase
    btnNewPhrase->setMaximumSize(100,25);
    btnNewPhrase->setMaximumSize(100,25);
    btnNewPhrase->setText(QString("New Phrase"));


    hlNewBtn->addSpacerItem(spacer2); // adds the spacer to new button layout
    hlNewBtn->addWidget(btnNewPhrase); // adds button to new button layout

    connect(btnNewPhrase, &QPushButton::clicked, this, &MainWindow::onNewPhraseClicked);

    vlMain->addLayout(hlNewBtn); // add sthe new button layout to the main layout

    _game->loadPhrases();
    _game->shufflePhrases();

    QString dashWord = QString::fromStdString(_game->newPhrase()); // gets new phrase in constructor

    lblPhrase->setText(dashWord); // sets the dash phrase in label

    draw(); // draw shows the gallows and new dash word

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
    QString dashWord = QString::fromStdString(_game->showHiddenPhrase()); // gets new phrase from model

    lblPhrase->setText(dashWord); // sets the dash phrase in label

    lblPicture->setStyleSheet(_imageFor.at(_game->showGallows()));

    // redraw letters
     for (auto btn : letters)
     {
         QString letter = btn->text();
         std::string guess = letter.toLocal8Bit().constData();
         if(_game->letterGuessed(guess))
         {
             btn->setEnabled(false);
         }
         else
            btn->setEnabled(true);
     }
     static bool windowHasBeenShown = false;
     if(_game->won() && !windowHasBeenShown)
     {
         windowHasBeenShown = true;
         QMessageBox msg;
         msg.setText("HOORAY!!! You Win!!!");
         msg.show();
         delay();
     }
     if(!_game->won())
     {
         windowHasBeenShown = false;
     }

     if(_game->lost())
     {
         QString word = QString::fromStdString(_game->showPhrase()); // gets new phrase from model

         lblPhrase->setText(word); // sets the dash phrase in label
     }
}

void MainWindow::onLetterClicked()
{
    //downcast. sender must be a QPushButton so downcast is safe

    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    btn->setEnabled(false);
    //qWarning() << btn->text();
    QString letter = btn->text();
    std::string guess = letter.toLocal8Bit().constData();
    _game->processGuess(guess);
    draw();
}

void MainWindow::onNewPhraseClicked()
{
    _game->initGame();
    _game->shufflePhrases();
    _game->newPhrase();
    draw();
}

void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(3);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

