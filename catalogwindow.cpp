#include "catalogwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QPixmap>
#include <QLabel>

CatalogWindow::CatalogWindow(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("植物与僵尸图鉴");
    setFixedSize(600, 500); // 窗口大小

    // 设置窗口背景图片
    this->setStyleSheet("CatalogWindow {"
                        "    background-image: url(:/images/Background3.png);"
                        "    background-repeat: no-repeat;"
                        "    background-position: center;"
                        "    background-size: cover;"
                        "}");

    // 主布局：左右两部分
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(40); // 左右部分的间距
    mainLayout->setContentsMargins(20, 20, 20, 20); // 主布局与窗口边框的填充

    /* ==================== 左侧：植物和僵尸列表 ==================== */
    listTabWidget = new QTabWidget(this);

    listTabWidget->setStyleSheet(
        "QTabWidget::pane { border: 0; }" // 去掉 TabWidget 外框
        "QTabBar::tab { background: rgba(255, 255, 255, 160); color: black; font-family: Calibri; font-weight: bold; padding: 10px; }"
        "QTabBar::tab:selected { background: rgba(255, 255, 255, 200); }"
        "QListWidget {"
        "    background: transparent;" // 背景透明
        "    color: black;"            // 设置文字为黑色
        "    border: none;"            // 去掉边框
        "    font-family: Calibri;"    // 字体设置为 Calibri
        "    font-weight: bold;"       // 设置字体加粗
        "    font-size: 14px;"         // 设置字体大小
        "}");

    // 植物列表
    plantListWidget = new QListWidget(listTabWidget);
    listTabWidget->addTab(plantListWidget, "植物列表");
    connect(plantListWidget, &QListWidget::currentItemChanged, this, &CatalogWindow::onPlantClicked);

    // 僵尸列表
    zombieListWidget = new QListWidget(listTabWidget);
    listTabWidget->addTab(zombieListWidget, "僵尸列表");
    connect(zombieListWidget, &QListWidget::currentItemChanged, this, &CatalogWindow::onZombieClicked);

    mainLayout->addWidget(listTabWidget, 5); // 左侧列表占比例 5

    /* ==================== 右侧：图片和文本描述 ==================== */
    QWidget *detailWidget = new QWidget(this);
    QVBoxLayout *detailLayout = new QVBoxLayout(detailWidget);
    detailLayout->setSpacing(60); // 上下部分的间距
    detailLayout->setContentsMargins(20, 20, 20, 20); // 右侧内容与边框的填充

    // 图片标签（上半部分）
    imageLabel = new QLabel(detailWidget);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);"); // 透明背景
    detailLayout->addWidget(imageLabel, 1);

    // 文本标签（下半部分）
    textLabel = new QLabel(" ", detailWidget);
    textLabel->setWordWrap(true);
    textLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    textLabel->setStyleSheet(
        "background-color: rgba(255, 255, 255, 0);"
        "font-family: 'Comic Sans MS', cursive;" // 设置手写体字体
        "color: #5D4037;"                        // 字体颜色设置为深棕色
        "font-size: 16px;"                       // 设置字体大小
        "font-weight: bold;"                     // 设置字体加粗
        "font-style: italic;"                    // 设置斜体风格
        );
    detailLayout->addWidget(textLabel, 3);

    mainLayout->addWidget(detailWidget, 6); // 右侧内容占比例 6

    /* ==================== 填充数据 ==================== */
    populatePlantList();
    populateZombieList();

    /* ==================== TabWidget 切换响应 ==================== */
    connect(listTabWidget, &QTabWidget::currentChanged, this, &CatalogWindow::onTabChanged);
}

CatalogWindow::~CatalogWindow()
{
    delete listTabWidget;
    delete plantListWidget;
    delete zombieListWidget;
    delete imageLabel;
    delete textLabel;
}

void CatalogWindow::populatePlantList()
{
    // 填充植物数据
    plantMap["豌豆射手"] = {"豌豆射手", "豌豆射手发射豌豆攻击僵尸", "100", "7.5秒", ":/images/Peashooter.png"};
    plantMap["坚果"] = {"坚果", "具有高生命值，用于挡住僵尸，可以使用它来保护其他植物", "50", "15秒", ":/images/WallNut.png"};
    plantMap["樱桃炸弹"] = {"樱桃炸弹", "樱桃炸弹对附近所有僵尸造成高伤害", "150", "20秒", ":/images/CherryBomb.png"};
    plantMap["寒冰射手"] = {"寒冰射手", "发射豌豆攻击僵尸，攻击附带霜冻效果，降低僵尸45%的移动速度和攻击速度", "175", "7.5秒", ":/images/SnowPea.png"};
    plantMap["土豆雷"] = {"土豆雷", " 土豆地雷能够给予敌人致命一击，不过在此之前，它需要时间武装一下自己。", "25", "10秒", ":/images/PotatoMine.png"};
    plantMap["双发射手"] = {"双发射手", "双发射手每次发射两枚豌豆攻击僵尸", "200", "7.5秒", ":/images/Repeater.png"};
    plantMap["向日葵"] = {"向日葵", "向日葵是收集额外阳光必不可少的植物。为什么不多种一些呢？", "50", "5秒", ":/images/SunFlower.png"};

    // 将植物名称添加到列表
    for (const auto &key : plantMap.keys()) {
        plantListWidget->addItem(key);
    }
}

void CatalogWindow::populateZombieList()
{
    // 填充僵尸数据
    zombieMap["普通僵尸"] = {"普通僵尸", "普通僵尸是园子里常见的僵尸，移动速度慢", "100", "1.0", ":/images/ZombieWalk1.gif"};
    zombieMap["路障僵尸"] = {"路障僵尸", "路障僵尸头顶的路障能抵挡一定的攻击，使他比普通僵尸强壮一些", "200", "1.0", ":/images/ConeZombieWalk.gif"};
    zombieMap["铁桶僵尸"] = {"铁桶僵尸", "铁通僵尸的铁桶使其格外耐打", "200", "1.0", ":/images/BucketZombieWalk.gif"};
    zombieMap["旗子僵尸"] = {"旗子僵尸", "旗帜僵尸代表着一大“波”僵尸的到来", "100", "1.0", ":/images/FlagZombieWalk.gif"};
    zombieMap["铁栅门僵尸"] = {"铁栅门僵尸", "铁栅门僵尸的铁栅门为其提供了一个400生命值的护盾。", "100+400", "1.0", ":/images/ScreenZombieWalk.gif"};
    zombieMap["橄榄球僵尸"] = {"橄榄球僵尸", "橄榄球僵尸勇往直前，一身的护甲使其格外耐打，移动速度极快", "600", "1.8", ":/images/FootballZombieWalk.gif"};

    // 将僵尸名称添加到列表
    for (const auto &key : zombieMap.keys()) {
        zombieListWidget->addItem(key);
    }
}

void CatalogWindow::onPlantClicked()
{
    QListWidgetItem *item = plantListWidget->currentItem();
    if (!item)
        return;

    QString plantName = item->text();
    if (plantMap.contains(plantName)) {
        const PlantInfo &plant = plantMap[plantName];
        textLabel->setText("名称: " + plant.name + "\n特点: " + plant.description +
                           "\n花费: " + plant.cost + " 阳光\n冷却时间: " + plant.cooldown);
        imageLabel->setPixmap(QPixmap(plant.imagePath).scaled(200, 200, Qt::KeepAspectRatio));
    }
}

void CatalogWindow::onZombieClicked()
{
    QListWidgetItem *item = zombieListWidget->currentItem();
    if (!item)
        return;

    QString zombieName = item->text();
    if (zombieMap.contains(zombieName)) {
        const ZombieInfo &zombie = zombieMap[zombieName];
        textLabel->setText("名称: " + zombie.name + "\n特点: " + zombie.description +
                           "\n血量: " + zombie.health + "\n移速: " + zombie.speed);
        imageLabel->setPixmap(QPixmap(zombie.imagePath).scaled(200, 200, Qt::KeepAspectRatio));
    }
}

void CatalogWindow::onTabChanged(int index)
{
    // 清空右侧区域
    imageLabel->clear();
    textLabel->setText("");

    if (index == 0) {
        // 切换到植物列表
        onPlantClicked();
    } else if (index == 1) {
        // 切换到僵尸列表
        onZombieClicked();
    }
}
