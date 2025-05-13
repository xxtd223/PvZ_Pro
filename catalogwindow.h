#ifndef CATALOGWINDOW_H
#define CATALOGWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QMap>

// 植物和僵尸结构体，用于存储信息
struct PlantInfo {
    QString name;
    QString description;
    QString cost;
    QString cooldown;
    QString imagePath;
};

struct ZombieInfo {
    QString name;
    QString description;
    QString health;
    QString speed;
    QString imagePath;
};

class CatalogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CatalogWindow(QWidget *parent = nullptr);
    ~CatalogWindow();

private slots:
    void onPlantClicked();         // 当选择植物列表中的项时更新右侧详情
    void onZombieClicked();        // 当选择僵尸列表中的项时更新右侧详情
    void onTabChanged(int index);  // 响应左侧 TabWidget 当前选项被切换

private:
    void populatePlantList();      // 填充植物数据
    void populateZombieList();     // 填充僵尸数据

    // 左侧的植物和僵尸列表
    QTabWidget *listTabWidget;
    QListWidget *plantListWidget;
    QListWidget *zombieListWidget;

    // 右侧的图片和描述部分
    QLabel *imageLabel;            // 用于显示植物或僵尸的图片
    QLabel *textLabel;             // 用于显示植物或僵尸文本

    // 存储植物和僵尸信息的 QMap
    QMap<QString, PlantInfo> plantMap;
    QMap<QString, ZombieInfo> zombieMap;
};

#endif // CATALOGWINDOW_H
