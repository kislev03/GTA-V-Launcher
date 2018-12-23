#ifndef INSTALLMODWINDOW_H
#define INSTALLMODWINDOW_H

#include "SelfDeleteDialog.h"
#include <QDir>
#include <QHideEvent>
#include "QCheckableFileSystemModel.h"
#include "QFileSystemModelDirectorySortProxy.h"

namespace Ui {
class InstallModWindow;
}

typedef struct{
		QStringList _detectedAsi;
		QStringList _detectedDll;
} modsStruct;

enum ModType{
	NONE = 0,
	ASI = 2,
	DLL = 4,
	BOTH = 6
};

inline ModType operator|(ModType a, ModType b){
	return static_cast<ModType>(static_cast<int>(a) | static_cast<int>(b));
}

inline ModType& operator|=(ModType& a, ModType b){
	a = a|b;
	return a;
}

class InstallModWindow : public SelfDeleteDialog
{
		Q_OBJECT

	public:
		explicit InstallModWindow(QString const& installDir, QString const& modsDir, QString const& scriptsDir, QWidget *parent = nullptr);
		~InstallModWindow() override;
	private slots:
		void validateEdit(const QString &text);
		void addMod();
	Q_SIGNALS:
		void modAdded(QString const& name) const;
	protected:
		virtual void retranslateUi() override;
	private:
		Ui::InstallModWindow *ui;
		QDir const _modsDir;
		QDir const _scriptsDir;
		QDir _installDir;
		QDir _currentDir;
		QCheckableFileSystemModel *_model = nullptr;
		QFileSystemModelDirectorySortProxy *_sortModel = nullptr;
		QHash<QString, ModType> _type;
		void clearInstallDirectory(bool mk = true);
		void copyAndExtractZip(const QString &zip) const;
		modsStruct detectModFiles(const QDir &dir) const;
		QSet<QString> detectNeededFiles(QDir _installDir, modsStruct detectedMods, bool takeAllConfigFiles);
		static void copyDir(QDir const& from, QDir const& to);
		void initFileSystemModel();
};

#endif // INSTALLMODWINDOW_H
