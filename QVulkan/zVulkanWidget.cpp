//
// Created by 32725 on 2023/6/5.
//

#include "zVulkanWidget.h"

zVulkanWidget::zVulkanWidget(QWindow *parent){
}

zVulkanWidget::~zVulkanWidget() {
}

QVulkanWindowRenderer *zVulkanWidget::createRenderer() {
	return new zVulkanRenderer(this);
}

zVulkanRenderer::zVulkanRenderer(QVulkanWindow *window) {

}

zVulkanRenderer::~zVulkanRenderer() {

}

void zVulkanRenderer::initResources() {
	QVulkanWindowRenderer::initResources();
}

void zVulkanRenderer::initSwapChainResources() {
	QVulkanWindowRenderer::initSwapChainResources();
}

void zVulkanRenderer::releaseSwapChainResources() {
	QVulkanWindowRenderer::releaseSwapChainResources();
}

void zVulkanRenderer::releaseResources() {
	QVulkanWindowRenderer::releaseResources();
}

void zVulkanRenderer::startNextFrame() {

}
