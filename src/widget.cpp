#include "widget.h"
#include "thread_url.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    tab_widget = new ClosableTabWidget(this);
    select_widget = new BoardSelectWidget(this);
    viewer_widget = new ViewerWidget(this);
    option_widget = new OptionWidget(this);
    catalog_widget = new CatalogWidget(this);

    tab_widget->addTab(select_widget,"Search");
    tab_widget->addTab(catalog_widget,"Catalogs");
    tab_widget->addTab(viewer_widget,"Viewer");
    tab_widget->addTab(option_widget,"Options");    

    tab_widget->setTabsClosable(true);

    loadFavourites();

    //textBrowserLog = new QTextBrowser(this);

    mainLayout->addWidget(tab_widget);
    setLayout(mainLayout);

    setMaximumHeight(1080);
    setMaximumWidth(1920);

    setMinimumHeight(768);
    setMinimumWidth(1024);

    connect(select_widget,SIGNAL(load_query(int)),this,SLOT(loadThread(int)));
    connect(select_widget,SIGNAL(load_query()),this,SLOT(loadThread()));
}

Widget::~Widget()
{

}

void Widget::loadThread()
{
    thread_widget = new ThreadWidget(select_widget->getThreadUrl().getBoard(),select_widget->getThreadUrl().getID(),false,select_widget->getPicsOnly(), this);

    QString name;
    Thread* thread = thread_widget->getThread();

    if(thread->hasTitle())
    {
        name = QString(thread->getTitle().c_str());
    }
    else
    {
        name = QString("/") +QString(select_widget->getBoard().c_str()) +QString("/") + QString::number(thread->getThreadID());
    }

    tab_widget->addTab(thread_widget,name);
}

void Widget::loadThread(int thread_index)
{
    thread_widget = new ThreadWidget(select_widget->getBoard().c_str(),select_widget->getThreadIDFromIndex(thread_index),false,select_widget->getPicsOnly(),this);

    QString name;
    Thread* thread = thread_widget->getThread();

    if(thread->hasTitle())
    {
        name = QString(thread->getTitle().c_str());
    }
    else
    {
        name = QString("/") +QString(select_widget->getBoard().c_str()) + QString("/") + QString::number(thread->getThreadID());
    }

    tab_widget->addTab(thread_widget,name);
}

void Widget::loadFavourites()
{
    /*Vérification de l'existence du fichier*/
    QFile Fout;
    Fout.setFileName(FAVORITE_THREADS_PATH);
    std::string file = std::string(FAVORITE_THREADS_PATH);
    std::string folder = file.substr(0,file.find_last_of("/")+1);

    checkFolder(folder);

    if(!Fout.exists())
    {
        Json::StyledWriter writer;
        Json::Value root_favourite;
        root_favourite[0]["board"] = "g";
        root_favourite[0]["id"] = 47100644;

        saveJSONFile(FAVORITE_THREADS_PATH, writer.write(root_favourite));
    }

    /*Chargement*/
    Json::Value root = loadJSONFile(FAVORITE_THREADS_PATH);

    int i = 0;
    while(root[i]["board"] != Json::nullValue)
    {
        thread_widget = new ThreadWidget(root[i]["board"].asCString(),root[i]["id"].asInt(),true,false,this);

        tab_widget->addTab(thread_widget,QString("/") +QString(root[i]["board"].asCString()) +QString("/") + QString::number(root[i]["id"].asInt()));

        i++;
    }
}

void Widget::setTab(int index)
{
    tab_widget->setCurrentIndex(index);
}
