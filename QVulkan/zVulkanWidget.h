//
// Created by 32725 on 2023/6/5.
//

#ifndef SUMARY_ZVULKANWIDGET_H
#define SUMARY_ZVULKANWIDGET_H
#include <QVulkanWindow>
#include <QVulkanInstance>
#include <QVulkanFunctions>
#include <QWidget>

class zVulkanRenderer:public QVulkanWindowRenderer {
public:
	explicit zVulkanRenderer(QVulkanWindow *window);
	~zVulkanRenderer() override;

	void initResources() override;
	void initSwapChainResources() override;
	void releaseSwapChainResources() override;
	void releaseResources() override;
	void startNextFrame() override;
};

class zVulkanWidget:public QVulkanWindow{
public:
	explicit zVulkanWidget(QWindow *parent = nullptr);
	~zVulkanWidget() override;

protected:
	QVulkanWindowRenderer* createRenderer() override;
};


#endif //SUMARY_ZVULKANWIDGET_H
