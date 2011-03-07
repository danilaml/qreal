#pragma once

class QIcon;

#include <QtCore/QDir>
#include <QtCore/QStringList>
#include <QtCore/QMap>
#include <QtCore/QPluginLoader>
#include <QtCore/QStringList>

#include "listenerManager.h"
#include "../umllib/uml_element.h"
#include "../kernel/NewType.h"
#include "../../qrmc/plugins/pluginInterface.h"

namespace qrRepo {
	class RepoApi;
}

namespace qReal {
	class EditorManager : public QObject
	{
		Q_OBJECT

	public:
		explicit EditorManager(QObject *parent = NULL);

                TypeList editors() const;
                TypeList diagrams(NewType const &editor) const;
                TypeList elements(NewType const &diagram) const;
                TypeList elementsOnDiagram(NewType const &diagramNode) const;
		bool loadPlugin(QString const &pluginName);
		bool unloadPlugin(QString const &pluginName);

                QString mouseGesture(NewType const &type) const;
                QString friendlyName(NewType const &type) const;
                QString description(NewType const &type) const;
                QString propertyDescription(NewType const &type, QString const &propertyName) const;
                QIcon icon(NewType const &type) const;
                UML::Element* graphicalObject(NewType const &type) const;

                TypeList getContainedTypes(const NewType &type) const;
                TypeList getConnectedTypes(const NewType &type) const;
                TypeList getUsedTypes(const NewType &type) const;
                QStringList getEnumValues(NewType const &type, const QString &name) const;
                QString getTypeName(NewType const &type, const QString &name) const;

                bool isEditor(NewType const &type) const;
                bool isDiagram(NewType const &type) const;
                bool isElement(NewType const &type) const;

                virtual QStringList getPropertyNames(NewType const &type) const;
                virtual QString getDefaultPropertyValue(NewType const &type, QString name) const;
                virtual QStringList getPropertiesWithDefaultValues(NewType const &type) const;

                TypeList checkNeededPlugins(qrRepo::RepoApi const &api) const;
                bool hasElement(NewType const &element) const;

                NewType findElementByType(QString const &type) const;
		QList<Listener *> listeners() const;

				EditorInterface* getEditorInterface(QString editor) const;
	private:
                void checkNeededPluginsRecursive(qrRepo::RepoApi const &api, Id const &id, TypeList &result) const;

		QStringList mPluginsLoaded;
		QMap<QString, QString> mPluginFileName;
		QMap<QString, EditorInterface *> mPluginIface;
		QMap<QString, QPluginLoader *> mLoaders;

		QDir mPluginsDir;
		QStringList mPluginFileNames;

                const NewType mRoot;
	};

}