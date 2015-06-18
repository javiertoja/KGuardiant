#include "console.h"

Console::Console(QObject *parent) :
    QThread(parent)
{
    out = false;

}

void Console::text()
{
    QTextStream qin(stdin);
    QString line = qin.readLine();
    option = line.toStdString().c_str()[0];
    parseOpts();
    showOpts();
}


/**
 * @brief Console::printClients
 * @param clients
 */
void Console::printClients(QHash<qintptr, TCPConnection *> *clients)
{
    QHashIterator<qintptr, TCPConnection *> *it
            = new QHashIterator<qintptr, TCPConnection *>(*clients);


    std::cout << std::endl;
    while(it->hasNext()){
        it->next();

        std::cout << "\t Cliente [" << it->key() << "]"
                  << "Fio ["
                  << it->value() << "]" << std::endl;
    }

}

/**
 * @brief Console::result
 * @param msg
 */
void Console::result(QString msg){

    std::cout << msg.toStdString() << std::endl;
}

/**
 * @brief Console::run
 */
void Console::run()
{
    notifier = new QSocketNotifier(STDIN_FILENO,QSocketNotifier::Read);
    connect(notifier,
            SIGNAL(activated(int)),
            this,
            SLOT(text()));
    exec();
}

/**
 * @brief Console::showOpts
 */
void Console::showOpts()
{
    std::cout << "Benvido" << std::endl;
    std::cout << "1.- Consultar clientes." << std::endl;
    std::cout << "2.- Iniciar servidor." << std::endl;
    std::cout << "3.- Deter detector." << std::endl;
    std::cout << "q.- Sair." << std::endl;
}

/**
 * @brief Console::parseOpts
 */
void Console::parseOpts()
{

    std::cout << "Elexindo [" << option << "]" << std::endl;
    switch(option) {
        case '1':{
            emit checkClients();
            break;
        }
        case '2':{
            emit startServer();
            break;
        }
        case '3':{
            emit stopServer();
            break;
        }
        case 'q':
            out = true;
            emit finish();
            break;

        default:
            return;
    }
}

/**
 * @brief Console::start
 */
void Console::startC()
{
    while (!out){
        showOpts();
        std::cin >> option;
        parseOpts();
    }
}

/**
 * @brief Console::stop
 */
void Console::stopC()
{
    out = true;
}
