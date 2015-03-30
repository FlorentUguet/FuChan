#ifndef BOARDSELECTWIDGET_H
#define BOARDSELECTWIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "constantes.h"
#include "post.h"
#include "clickableLabel.h"
#include "Workers/caching_worker.h"

class BoardSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoardSelectWidget(QWidget *parent = 0);
    ~BoardSelectWidget();

    std::string getBoard();
    int getThreadIDFromIndex(int index);

signals:
    void load_query(int thread_index);

public slots:
    void thread_load_toggled(int i);
    void startLoadingOPs(int i);
    void startLoadingOPs();
    void startDownloadThumbnails();
    void loadOP(int index);
    
private:
    std::string url;
    std::string outfilename;
    std::string board;
    int page;
    int post_number;
    int loaded_posts;

    QSignalMapper *mapper;
    QLabel *label_board;
    QLineEdit *line_edit_board;
    QComboBox *comboBoxPage;

    QVBoxLayout *mainLayout;
    QHBoxLayout *layoutBoard;

    QVBoxLayout *layoutProgress;
    QProgressBar *progressBar;
    QLabel *progresslabel;
    
    QWidget *w;
    QGridLayout *layoutThreads;
    QHBoxLayout *layoutThread[15];
    QPushButton *label_thread_no[15];
    QLabel *label_thumbnail[15];
    QTextBrowser *label_thread_subject[15];
    
    Post *thread_op[MAX_POST_NUMBER];

    QThread *qThread;
    CachingWorker *worker;

    QThread *thumb_thread[MAX_OP_NUMBER];
    CachingWorker *thumb_worker[MAX_OP_NUMBER];
};

#endif // BOARDSELECTWIDGET_H