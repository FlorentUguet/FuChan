#include "thread.h"
#include "fonctions.h"
#include "fonctions_json.h"

#include <cstdlib>

#include "Widget/post_widget.h"

Thread::Thread(std::string board, int thread_number)
{
    load(board, thread_number);
}

Thread::Thread()
{

}

Thread::~Thread()
{

}

void Thread::load(std::string board, int thread_number)
{
    std::string url = std::string(APIURL) + board + std::string("/thread/") + intToString(thread_number) + std::string(".json");
    std::string outfilename = std::string(CACHE_PATH) + board + "/posts/" + intToString(thread_number) + std::string(".json");

    checkFolder(std::string(CACHE_PATH) + board + "/posts/");
    cachingFile(url.c_str(),strdup(outfilename.c_str()),true,false);

    int i=0;

    Json::Value root = loadJSONFile(outfilename.c_str());
    saveAndLoad(root,outfilename.c_str());

    while(root["posts"][i] != Json::nullValue)
    {
        post_list.push_back(new Post(root["posts"][i],board));
        posts_ids.push_back(root["posts"][i]["no"].asInt());
        i++;
        if(i>MAX_POST_NUMBER){exit(1);}
    }

    post_count = i;

    for(int j=i;j<MAX_POST_NUMBER;j++)
    {
        posts_json.assign(j,Json::nullValue);
        posts_ids.assign(j, 0);
    }

    std::string output = std::string("Thread ") + intToString(thread_number) + std::string(" from ") + board + std::string(" loaded.");
    outputInfo("INFO",
               output,
               LEVEL_THREAD);
    board_id = board;
    thread_id = thread_number;

    increaseThreadLoaded();
}

int Thread::getPostCount()
{
    return post_count;
}

Post* Thread::getPost(int i)
{
    return post_list.at(i);
}

int Thread::getThreadID()
{
    return thread_id;
}

std::vector<Post*> Thread::getPostList()
{
    return post_list;
}

std::string Thread::getTitle()
{
    return getPost(0)->getSubject();
}

std::string Thread::getTitleSimple()
{
    return getPost(0)->getSemanticUrl();
}

bool Thread::hasTitle()
{
    return !getPost(0)->getSubject().empty();
}
