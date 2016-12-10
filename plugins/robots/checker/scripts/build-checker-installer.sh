#!/bin/bash -x
# Copyright 2015 CyberTech Labs Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set -o nounset
set -o errexit

<<<<<<< HEAD

function show_help {
	echo "Usage: build-checker-installer.sh [<path to Qt with version>] [<path to QReal>] [<path to directory with fields>] [<path to directory with examples>] [<path to directory with tasks>] [<path to directory with inputs>]"
	echo "<path to Qt with version> --- root of your Qt installation with version release build of qrealRobots.pro"
	echo "<path to QReal> --- path to QReal sources root (with completed release build of qrealRobots.pro)."
	echo "                    Defaults to \"../..\""
	echo "<path to \"fields\" directory> --- path to directory with prepared fields."
	echo "                                   Defaults to \"<path to QReal/qrtest/trikStudioSimulatorTests/fields/fields>.\""
	echo "<path to \"examples\" directory> --- path to directory with example saves."
	echo "                                     Defaults to \"<path to QReal/qrtest/trikStudioSimulatorTests/solutions>.\""
	echo "<path to \"tasks\" directory> --- path to directory with saves with tasks."
	echo "                                  Defaults to \"<path to QReal/qrtest/trikStudioSimulatorTests/tasks>.\""
	echo "<path to \"inputs\" directory> --- path to directory with saves with inputs."
	echo "                                  Defaults to \"<path to QReal/qrtest/trikStudioSimulatorTests/inputs>.\""
	echo "Example: ./build-checker-installer.sh ~/Qt ~/stepic-examples"
	exit 0
}



cd "$(dirname "$0")"

QT_ARCH=$(qmake -query QT_HOST_DATA)
#QT_ARCH=$(qmake -query QT_INSTALL_ARCHDATA)
if [ "$#" -lt 1 ]; then
	qtDir=$(readlink -f $QT_ARCH)
	qtDirForPlugins=$(readlink -f $qtDir/plugins)
	qtDirForSo=$(readlink -f $qtDir/../)
else
	ARG1=$(readlink -f $1)
	qtDir=$(readlink -f $ARG1)
	qtDirGcc=$(readlink -f $qtDir/gcc_64)
	qtDirForPlugins=$(readlink -f $qtDirGcc/plugins)
	qtDirForSo=$(readlink -f $qtDirGcc/lib)
fi


#qtDir=${ARG1-:$QT_ARCH}
#echo qtDir=$qtDir
#[ "x$qtDir" == "x" ] && show_help || :

=======
function check_qmake_version {
        
#	echo Here
	make -f <(echo -e "-include $1/Makefile\ncheck_qmake_version: FORCE\n\t@echo \${QMAKE}") check_qmake_version
}

function show_help {
	echo "Usage: $(basename $0) [QREAL_DIR [FIELDS_DIR EXAMPLES_DIR TASKS_DIR] ]"
	echo -e "QREAL_DIR\t-\tPath to QReal sources root"
	echo "                    Defaults to \"../..\""
	echo -e "FIELDS_DIR\t-\tPath to directory with prepared fields."
	echo "                                   Defaults to \"$$QREAL_DIR/qrtest/trikStudioSimulatorTests/fields/fields\""
	echo -e "EXAMPLES_DIR\t-\tPath to examples dir"
	echo "                                     Defaults to \"$$QREAL_DIR/qrtest/trikStudioSimulatorTests/solutions\""
	echo -e "TASKS_DIR\t-\tPath to folder with saves with tasks."
	echo "                                  Defaults to \"$$QREAL_DIR/qrtest/trikStudioSimulatorTests/tasks\""
	echo "                                  Defaults to \"<path to QReal/qrtest/trikStudioSimulatorTests/inputs>.\""
	echo "Example: ./$(basename $0) ~/Qt/5.7 ~/stepic-examples"
	exit 0
}

[ "$*" == "--help" ] && show_help || :

pushd "$(dirname "$0")"
>>>>>>> 6cd2eb3299a352fe680c32ee5d5bb8340b0c484d

if [ "$#" -gt 1 ]; then
	qRealDir=$(readlink -f $1)
else
	qRealDir=$(readlink -f ../..)
fi

QMAKE=$(check_qmake_version $qRealDir)
echo "Using qmake: $QMAKE"
QT_HOST_DATA=$($QMAKE -query QT_HOST_DATA)
QT_INSTALL_PLUGINS=$($QMAKE -query QT_INSTALL_PLUGINS)
QT_INSTALL_LIBS=$($QMAKE -query QT_INSTALL_LIBS)
QT_HOST_LIBS=$($QMAKE -query QT_HOST_LIBS)

if [ "$#" -lt 1 ]; then
	qtDir=$(readlink -f $QT_HOST_DATA)
	qtDirForPlugins=$(readlink -f $QT_INSTALL_PLUGINS)
	qtDirLib=$(readlink -f $QT_INSTALL_LIBS)
	hostDirLib=$(readlink -f $QT_HOST_LIBS)
fi


COPY="cp -rfP"
NEED_QT_LIBS=false

if [ "$#" -gt 2 ]; then
	fieldsDir=$(readlink -f $2)
else
	fieldsDir=$(readlink -f $qRealDir/qrtest/trikStudioSimulatorTests/fields/fields)
fi

if [ "$#" -gt 3 ]; then
	examplesDir=$(readlink -f $3)
else
	examplesDir=$(readlink -f $qRealDir/qrtest/trikStudioSimulatorTests/solutions)
fi

if [ "$#" -gt 4 ]; then
	tasksDir=$(readlink -f $4)
else
	tasksDir=$(readlink -f $qRealDir/qrtest/trikStudioSimulatorTests/tasks)
fi

if [ "$#" -gt 5 ]; then
<<<<<<< HEAD
	inputsDir=$(readlink -f $6)
=======
	inputsDir=$(readlink -f $5)
>>>>>>> 6cd2eb3299a352fe680c32ee5d5bb8340b0c484d
else
	inputsDir=$(readlink -f $qRealDir/qrtest/trikStudioSimulatorTests/inputs)
fi

<<<<<<< HEAD
=======
rm -rf trikStudio-checker
>>>>>>> 6cd2eb3299a352fe680c32ee5d5bb8340b0c484d
mkdir -p trikStudio-checker/bin
pushd trikStudio-checker/bin

if $NEED_QT_LIBS ; then
    LIBS=$(ldd ./qreal | grep so | sed -e '/^[^\t]/ d' | sed -e 's/\t//' | sed -e 's/.*=..//' | sed -e 's/ (0.*)//' | sort -u | grep -Ev '^\.|^/lib')

# Copying required Qt libraries
<<<<<<< HEAD
cp -rf $qtDirForPlugins/iconengines .

mkdir -p imageformats
cp -fP $qtDirForPlugins/imageformats/libqsvg.so imageformats/

mkdir -p platforms
cp -fP $qtDirForPlugins/platforms/libqminimal.so platforms/

cp -fP $qtDirForSo/libicudata.so* .
cp -fP $qtDirForSo/libicui18n.so* .
cp -fP $qtDirForSo/libicuuc.so* .
cp -fP $qtDirForSo/libQt5Core.so* .
cp -fP $qtDirForSo/libQt5Gui.so* .
cp -fP $qtDirForSo/libQt5Network.so* .
cp -fP $qtDirForSo/libQt5PrintSupport.so* .
cp -fP $qtDirForSo/libQt5Script.so* .
cp -fP $qtDirForSo/libQt5Svg.so* .
cp -fP $qtDirForSo/libQt5Widgets.so* .
cp -fP $qtDirForSo/libQt5Xml.so* .
cp -fP $qtDirForSo/libQt5DBus.so* .
=======
    ${COPY} $qtDirForPlugins/iconengines .

    mkdir -p imageformats
    ${COPY} $qtDirForPlugins/imageformats/libqsvg.so imageformats/

    mkdir -p platforms
    ${COPY} $qtDirForPlugins/platforms/libqminimal.so platforms/


    for lib in ${LIBS}; do ${COPY} $lib* .; done

# Seems like this code is obsolete, but ...
    ${COPY} $qtDirLib/libQt5Core.so* $qtDirLib/libQt5Gui.so* $qtDirLib/libQt5Network.so* \
        $qtDirLib/libQt5PrintSupport.so* $qtDirLib/libQt5Script.so* $qtDirLib/libQt5Svg.so* \
        $qtDirLib/libQt5Widgets.so* $qtDirLib/libQt5Xml.so* $qtDirLib/libQt5DBus.so* .

fi 
>>>>>>> 6cd2eb3299a352fe680c32ee5d5bb8340b0c484d

# Copying QReal libraries
cp -fP $qRealDir/bin/release/changelog.txt .
cp -fP $qRealDir/bin/release/libqrgraph.so* .
<<<<<<< HEAD
cp -fP $qRealDir/bin/release/libqrgui-meta-meta-model.so* .
=======
>>>>>>> 6cd2eb3299a352fe680c32ee5d5bb8340b0c484d
cp -fP $qRealDir/bin/release/libqrgui-brand-manager.so* .
cp -fP $qRealDir/bin/release/libqrgui-controller.so* .
cp -fP $qRealDir/bin/release/libqrgui-dialogs.so* .
cp -fP $qRealDir/bin/release/libqrgui-editor.so* .
cp -fP $qRealDir/bin/release/libqrgui-facade.so* .
cp -fP $qRealDir/bin/release/libqrgui-meta-meta-model.so* .
cp -fP $qRealDir/bin/release/libqrgui-models.so* .
cp -fP $qRealDir/bin/release/libqrgui-mouse-gestures.so* .
cp -fP $qRealDir/bin/release/libqrgui-plugin-manager.so* .
cp -fP $qRealDir/bin/release/libqrgui-preferences-dialog.so* .
cp -fP $qRealDir/bin/release/libqrgui-text-editor.so* .
cp -fP $qRealDir/bin/release/libqrgui-thirdparty.so* .
cp -fP $qRealDir/bin/release/libqrgui-tool-plugin-interface.so* .
cp -fP $qRealDir/bin/release/libqrkernel.so* .
cp -fP $qRealDir/bin/release/libqrrepo.so* .
cp -fP $qRealDir/bin/release/libqrtext.so* .
cp -fP $qRealDir/bin/release/libqrutils.so* .
cp -fP $qRealDir/bin/release/libqscintilla2.so* .
cp -fP $qRealDir/bin/release/libqslog.so* .
cp -fP $qRealDir/bin/release/libqrtext.so* .

mkdir -p translations/ru
cp -fP $qRealDir/bin/release/translations/ru/qrgui_dialogs_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrgui_editor_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrgui_hotKeyManager_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrgui_mainWindow_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrgui_models_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrgui_mouseGestures_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrgui_pluginsManager_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrgui_preferencesDialog_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrgui_system_facade_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrgui_textEditor_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrgui_thirdparty_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrgui_toolPluginInterface_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrtext_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qrutils_ru.qm ./translations/ru/
cp -fP $qRealDir/bin/release/translations/ru/qt_ru.qm ./translations/ru/

# Copying TRIKStudio plugins
cp -fP $qRealDir/bin/release/libqextserialport.so* .
cp -fP $qRealDir/bin/release/librobots-2d-model.so* .
cp -fP $qRealDir/bin/release/librobots-interpreter-core.so* .
cp -fP $qRealDir/bin/release/librobots-trik-kit-interpreter-common.so* .
cp -fP $qRealDir/bin/release/librobots-kit-base.so* .
cp -fP $qRealDir/bin/release/librobots-trik-kit.so* .
cp -fP $qRealDir/bin/release/librobots-utils.so* .

mkdir -p plugins/editors
cp -fP   $qRealDir/bin/release/plugins/editors/librobotsMetamodel.so ./plugins/editors/

mkdir -p plugins/tools
cp -fP $qRealDir/bin/release/plugins/tools/librobots-plugin.so ./plugins/tools/

mkdir -p plugins/tools/kitPlugins
cp -fP $qRealDir/bin/release/plugins/tools/kitPlugins/librobots-trik-v6-interpreter.so ./plugins/tools/kitPlugins/
cp -fP $qRealDir/bin/release/plugins/tools/kitPlugins/librobots-trik-v62-interpreter.so ./plugins/tools/kitPlugins/

mkdir -p translations/ru/plugins/robots
cp -fP $qRealDir/bin/release/translations/ru/plugins/robots/interpreterCore_ru.qm ./translations/ru/plugins/robots/
cp -fP $qRealDir/bin/release/translations/ru/plugins/robots/kitBase_ru.qm ./translations/ru/plugins/robots/
cp -fP $qRealDir/bin/release/translations/ru/plugins/robots/robotsMetamodel_ru.qm ./translations/ru/plugins/robots/
cp -fP $qRealDir/bin/release/translations/ru/plugins/robots/robotsPlugin_ru.qm ./translations/ru/plugins/robots/
cp -fP $qRealDir/bin/release/translations/ru/plugins/robots/robots_utils_ru.qm ./translations/ru/plugins/robots/
cp -fP $qRealDir/bin/release/translations/ru/plugins/robots/trikKitInterpreterCommon_ru.qm ./translations/ru/plugins/robots/
cp -fP $qRealDir/bin/release/translations/ru/plugins/robots/trikV6KitInterpreter_ru.qm ./translations/ru/plugins/robots/
cp -fP $qRealDir/bin/release/translations/ru/plugins/robots/trikV62KitInterpreter_ru.qm ./translations/ru/plugins/robots/
cp -fP $qRealDir/bin/release/translations/ru/plugins/robots/twoDModel_ru.qm ./translations/ru/plugins/robots/
cp -fP $qRealDir/bin/release/translations/ru/plugins/robots/twoDModelRunner_ru.qm ./translations/ru/plugins/robots/

# Copying checker itself
cp -fP $qRealDir/bin/release/2D-model .
cp -fP $qRealDir/bin/release/patcher .
cp -fP $qRealDir/bin/release/check-solution.sh .

cd ..
cp -fP $qRealDir/bin/release/checker.sh .

# Copying fields, examples and tasks
cp -r $fieldsDir ./fields
cp -r $examplesDir ./examples
cp -r $tasksDir ./tasks
cp -r $inputsDir ./inputs

# Packing
popd

tar cvfJ trik_checker.tar.xz trikStudio-checker

<<<<<<< HEAD
tar cvfz trik_checker.tar.gz trikStudio-checker
rm -rf trikStudio-checker

=======
>>>>>>> 6cd2eb3299a352fe680c32ee5d5bb8340b0c484d
