#include "ResourceStatusDisplayWidget.h"
#include "ui_ResourceStatusDisplayWidget.h"

#include "InvokeInEventLoop.h"

#include <QDateTime>

ResourceStatusDisplayWidget::ResourceStatusDisplayWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ResourceStatusDisplayWidget)
{
	ui->setupUi(this);
}

ResourceStatusDisplayWidget::~ResourceStatusDisplayWidget()
{
	delete ui;
}

void ResourceStatusDisplayWidget::update(ResourcePayload status)
{
	callFnDeferredAsync(this, [=]() mutable
	{
		if (status.usedReceiveQueue == 0)
		{
			status.freeReceiveQueue = 255;
		}

		ui->freePages->setText(QString::number(status.freePages) + " (" + QString::number(status.freePages * status.pageSize) + " Bytes)");
		ui->usedPages->setText(QString::number(status.usedPages) + " (" + QString::number(status.usedPages * status.pageSize) + " Bytes)");
		ui->pageSize->setText(QString::number(status.pageSize) + " Bytes");
		ui->taskQueueLoad->setText(QString::number(status.taskQueueLoad) + " Tasks");
		ui->freeReceiveBuffer->setText(QString::number(status.freeReceiveQueue) + " Bytes");
		ui->usedReceiveBuffer->setText(QString::number(status.usedReceiveQueue) + " Bytes");

		ui->barTaskQueueLoad->setMaximum(256);
		ui->barTaskQueueLoad->setValue(status.taskQueueLoad);

		ui->barUsedPagesProgressBar->setMaximum(status.usedPages + status.freePages);
		ui->barUsedPagesProgressBar->setValue(status.usedPages);

		ui->barReceiveBufferUsage->setMaximum(status.freeReceiveQueue + status.usedReceiveQueue);
		ui->barReceiveBufferUsage->setValue(status.usedReceiveQueue);

		ui->lastUpdate->setText(QDateTime::currentDateTime().toString());
	});
}
