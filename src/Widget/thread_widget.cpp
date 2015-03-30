#include "thread_widget.h"

#define WIDTH_MARGIN 68

ThreadWidget::ThreadWidget(std::string board, int thread_number, bool favourite, Widget *parent) : QWidget(parent)
{
    QHBoxLayout *layoutButtons = new QHBoxLayout;
    mapper = new QSignalMapper;
    thread_board = board;
    thread_id = thread_number;

    parent_widget = parent;

    setParent(parent);

    push_button_update = new QPushButton("Update",this);
    push_button_favourite = new QPushButton("Set as Favourite",this);
    push_button_favourite->setCheckable(true);
    push_button_favourite->setChecked(favourite);

    if(push_button_favourite->isChecked())
    {
        push_button_favourite->setText("Favourited");
    }

    layoutButtons->addWidget(push_button_update);
    layoutButtons->addWidget(push_button_favourite);

    scrollArea = new QScrollArea(this);
    areaWidget = new QWidget(this);
    areaWidget->setContentsMargins(5,5,5,5);

    secondaryLayout = new QGridLayout;

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutButtons);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    connect(push_button_update,SIGNAL(clicked()),this,SLOT(reload()));

    connect(push_button_favourite,SIGNAL(toggled(bool)),this,SLOT(toggleFavourite(bool)));

    connect(mapper, SIGNAL(mapped(int)), this, SLOT(setViewer(int)));

    load();
}

ThreadWidget::~ThreadWidget()
{
    for(int j=0;j<MAX_POST_NUMBER;j++)
    {

        delete posts[j];
    }

    delete thread;
    delete secondaryLayout;
}

void ThreadWidget::reload()
{
    delete secondaryLayout;
    delete thread;

    /*Suppression des posts précédents*/
    for(int j=0;j<MAX_POST_NUMBER;j++)
    {
        delete posts[j];
    }
    load();
}

void ThreadWidget::toggleFavourite(bool state)
{
    Json::Value root = loadJSONFile(FAVORITE_THREADS_PATH);
    Json::StyledWriter writer;
    int i = 0;
    if(state)
    {
        while(root[i]["board"] != Json::nullValue){i++;}
        root[i]["board"] = thread_board;
        root[i]["id"] = thread_id;
        saveJSONFile(FAVORITE_THREADS_PATH, writer.write(root));
        push_button_favourite->setText("Favourited");
    }
    else
    {
        while(root[i]["id"].asInt() != thread_id){i++;}
        root[i] = Json::nullValue;
        saveJSONFile(FAVORITE_THREADS_PATH, writer.write(root));
        push_button_favourite->setText("Set as Favourite");
    }
}


void ThreadWidget::load()
{
    thread = new Thread(thread_board,thread_id);

    secondaryLayout = new QGridLayout;

    int row = 0;

    /*Génération des posts*/
    for(int i=0;i<thread->getPostCount();i++)
    {
        posts[i] = new PostWidget(thread->getPost(i));

        if(i == 0)
        {
            posts[i]->setMaximumWidth(parent_widget->width()-WIDTH_MARGIN);
            posts[i]->setMinimumWidth(parent_widget->width()-WIDTH_MARGIN);
            secondaryLayout->addWidget(posts[i],0,0,1,2);
            posts[i]->setCommentBoxPolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            row++;
        }
        else if(!isPair(i))
        {
            posts[i]->setMaximumWidth((parent_widget->width()-WIDTH_MARGIN)/2);
            posts[i]->setMinimumWidth((parent_widget->width()-WIDTH_MARGIN)/2);
            secondaryLayout->addWidget(posts[i],row,0);
        }
        else
        {
            posts[i]->setMaximumWidth((parent_widget->width()-WIDTH_MARGIN)/2);
            posts[i]->setMinimumWidth((parent_widget->width()-WIDTH_MARGIN)/2);
            secondaryLayout->addWidget(posts[i],row,1);
            row++;
        }

        mapper->setMapping(posts[i]->thumb, i);
        connect(posts[i]->thumb, SIGNAL(clicked()), mapper , SLOT(map()));
    }

    for(int j=thread->getPostCount();j<MAX_POST_NUMBER;j++)
    {
        posts[j] = NULL;
    }

    areaWidget->setLayout(secondaryLayout);
    scrollArea->setWidget(areaWidget);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ThreadWidget::setViewer(int sender)
{
    outputInfo("DEBUG",
               std::string("Loading picture ") + intToString(sender),
               LEVEL_TOP_WIDGET);
    parent_widget->viewer_widget->load_picture(thread->getPost(sender));
    parent_widget->setTab(1);
}
