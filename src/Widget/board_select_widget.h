#ifndef BOARDSELECTWIDGET_H
#define BOARDSELECTWIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "constantes.h"
#include "post.h"
#include "clickableLabel.h"
#include "Workers/caching_worker.h"
#include "../thread_url.h"

#include "op_widget.h"

#include <vector>
#include <ostream>
#include <iomanip>

#include "stats.h"

class BoardSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoardSelectWidget(QWidget *parent = 0);
    ~BoardSelectWidget();

    std::string generateBoardLabel(std::string board, std::string title);
    std::string getBoard();
    int getThreadIDFromIndex(int index);

    int getThread();
    bool getPicsOnly();

    ThreadURL getThreadUrl();

signals:
    void load_query(int thread_index);
    void load_query();

public slots:
    void thread_load_toggled(int i);
    void thread_load_toggled();
    void startLoadingOPs(QString string);
    void startLoadingOPs(int i);
    void startLoadingOPs();
    void startDownloadThumbnails();
    void loadOP(int index);
    
private:
    std::vector<int> op_widgets_ids;
    std::vector<std::string> board_labels;
    std::vector<std::string> board_list;
    std::string url;
    std::string outfilename;
    std::string board;
    int page;
    int post_number;
    int loaded_posts;

    ThreadURL thread_url;

    QSignalMapper *mapper;

    QVBoxLayout *searchLayout;
    QHBoxLayout *layoutTop;

    QHBoxLayout *layoutBoard;
    QLabel *label_board;
    QComboBox *combo_box_board;
    QComboBox *comboBoxPage;
    QCheckBox *check_box_pic_only;

    QHBoxLayout *layoutManualThread;
    QLabel *labelThread;
    QLineEdit *lineEditThread;

    QVBoxLayout *mainLayout;

    QVBoxLayout *layoutProgress;
    QProgressBar *progressBar;
    QLabel *progresslabel;
    
    QWidget *w;
    QGridLayout *layoutThreads;

    std::vector<OPWidget*> op_widgets;
    
    Post *thread_op[MAX_POST_NUMBER];

    QThread *qThread;
    CachingWorker *worker;

    QThread *thumb_thread[MAX_OP_NUMBER];
    CachingWorker *thumb_worker[MAX_OP_NUMBER];
};

#endif // BOARDSELECTWIDGET_H
