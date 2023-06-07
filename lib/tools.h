//
// Created by 32725 on 2023/6/3.
//

#ifndef SUMARY_TOOLS_H
#define SUMARY_TOOLS_H
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHostAddress>

namespace tools {
	bool validIP(const QString &IP);
	class IPPort : public QWidget{
		Q_OBJECT
	public:
		explicit IPPort(QWidget *parent = nullptr);
		~IPPort() override;
		inline const QHostAddress& getIP(){return *address;}
		[[nodiscard]] inline auto getButton()const{return startButton;}
		[[nodiscard]] inline uint16_t getPort() const{return Port;}

		template<class T>
		void RegisterForStart(T&&func){
			connect(startButton,&QPushButton::clicked,this,std::forward<T>(func));
		}
	private:
		QString IP;
		uint16_t Port=11455;
		QHostAddress *address;
		QLineEdit *ip;
		QLineEdit *port;
		QLabel *IPLabel, *portLabel;
		QPushButton* startButton;
	};

	class FileTranslator:public QWidget{
		Q_OBJECT
	public:
		explicit FileTranslator(QWidget *parent = nullptr);
		~FileTranslator() override;
	private:
		QPushButton *send, *receive;
	};

};


#endif //SUMARY_TOOLS_H
