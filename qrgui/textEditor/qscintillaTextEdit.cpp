/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "qscintillaTextEdit.h"

#include <QtWidgets/QShortcut>

#include <thirdparty/qscintilla/Qt4Qt5/Qsci/qsciapis.h>

using namespace qReal;
using namespace text;

static const int circleMarkerNum = 1;

QScintillaTextEdit::QScintillaTextEdit()
	: mRole(0)
{
	init();
}

QScintillaTextEdit::QScintillaTextEdit(const QPersistentModelIndex &index, const int &role)
	: mIndex(index)
	, mRole(role)
{
	init();
}

QScintillaTextEdit::~QScintillaTextEdit()
{
	emit textSaved(text(), mIndex, mRole);
}

LanguageInfo QScintillaTextEdit::currentLanguage() const
{
	return mLanguage;
}

QVector<int> QScintillaTextEdit::getMarkedLines() const
{
	unsigned int mask = 0xFFFFFFFF;
	QVector<int> res;
	int curline = markerFindNext(0, mask);
	while (curline != -1) {
		res.append(curline);
		curline = markerFindNext(curline + 1, mask);
	}
	return res;
}

void QScintillaTextEdit::setCurrentLanguage(const LanguageInfo &language)
{
	setLexer(0);

	mLanguage = language;
	setIndentationsUseTabs(mLanguage.tabIndentation);
	setTabWidth(mLanguage.tabSize);
	setLexer(mLanguage.lexer);

	if (mLanguage.lexer) {
		QsciAPIs * const api = new QsciAPIs(mLanguage.lexer);
		for (const QString &additionalToken : mLanguage.additionalAutocompletionTokens) {
			api->add(additionalToken);
		}

		api->prepare();
	}
}

QString QScintillaTextEdit::editorId() const
{
	return "qReal.TextEditor." + QString::number(mIndex.internalId());
}

bool QScintillaTextEdit::supportsZooming() const
{
	return true;
}

bool QScintillaTextEdit::supportsCopying() const
{
	return true;
}

bool QScintillaTextEdit::supportsPasting() const
{
	return true;
}

bool QScintillaTextEdit::supportsCutting() const
{
	return true;
}

void QScintillaTextEdit::zoomIn()
{
	QsciScintilla::zoomIn();
}

void QScintillaTextEdit::zoomOut()
{
	QsciScintilla::zoomOut();
}

void QScintillaTextEdit::copy()
{
	QsciScintilla::copy();
}

void QScintillaTextEdit::paste()
{
	QsciScintilla::paste();
}

void QScintillaTextEdit::cut()
{
	QsciScintilla::cut();
}

void QScintillaTextEdit::init()
{
	// For some reason c++11-style connections do not work here!
	connect(this, SIGNAL(textChanged()), this, SLOT(emitTextWasModified()));
	setDefaultSettings();
	setCurrentLanguage(Languages::textFileInfo("*.txt"));
}

void QScintillaTextEdit::setDefaultSettings()
{
	// Current line highlighting
	setCaretLineVisible(true);
	setCaretLineBackgroundColor(QColor("gainsboro"));

	// Auto indent
	setAutoIndent(true);
	setIndentationGuides(false);

	// Tab size will be used
	setIndentationWidth(0);

	// Whitespaces visibility
	setWhitespaceVisibility(QsciScintilla::WsInvisible);

	// Show margin with line numbers (up to 1000)
	setMarginsBackgroundColor(QColor("gainsboro"));
	setMarginLineNumbers(1, true);
	setMarginWidth(1, QString("1000"));

	// Allow placing "breakpoints"
	setMarginSensitivity(1, true);
	markerDefine(QsciScintilla::Circle, circleMarkerNum);
	setMarkerBackgroundColor(QColor("red"));
	connect(this, SIGNAL(marginClicked(int,int,Qt::KeyboardModifiers))
			, this, SLOT(onMarginClicked(int,int,Qt::KeyboardModifiers)));

	// Autocompletion of lexems
	setAutoCompletionSource(QsciScintilla::AcsAll);
	setAutoCompletionCaseSensitivity(true);
	setAutoCompletionReplaceWord(true);
	setAutoCompletionShowSingle(true);
	setAutoCompletionThreshold(1);

	// Autohighlighting of brackets
	setBraceMatching(QsciScintilla::SloppyBraceMatch);
	setMatchedBraceBackgroundColor(Qt::yellow);
	setUnmatchedBraceForegroundColor(Qt::blue);

	// EOL symbol
#if defined Q_OS_X11
	setEolMode(QsciScintilla::EolUnix);
#elif defined Q_OS_WIN
	setEolMode(QsciScintilla::EolWindows);
#elif defined Q_OS_MAC
	setEolMode(QsciScintilla::EolMac);
#endif

	// Input encoding
	setUtf8(true);

	// Ctrl + Space Autocomplete
	QShortcut * const ctrlSpace = new QShortcut(QKeySequence("Ctrl+Space"), this);
	connect(ctrlSpace, &QShortcut::activated, this, &QScintillaTextEdit::autoCompleteFromAll);
}

void QScintillaTextEdit::emitTextWasModified()
{
	emit textWasModified(this);
}

void QScintillaTextEdit::onMarginClicked(int margin, int line, Qt::KeyboardModifiers state)
{
	Q_UNUSED(margin);
	Q_UNUSED(state);
	if (markersAtLine(line)) {
		markerDelete(line, circleMarkerNum);
	} else {
		markerAdd(line, circleMarkerNum);
	}
}
