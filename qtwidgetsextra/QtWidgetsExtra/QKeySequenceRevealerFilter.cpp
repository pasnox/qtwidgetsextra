#include "QKeySequenceRevealerFilter.h"

#include <QHelpEvent>
#include <QKeySequence>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QToolButton>
#include <QToolTip>
#include <QWhatsThis>

#include <optional>

using WidgetSequence = QPair<QWidget *, QKeySequence>;
using WidgetToolTip = QPair<QWidget *, QString>;

template <typename Button>
static std::optional<WidgetSequence> buttonEffectiveShortcut(Button *button) {
    if (!button) {
        return {};
    }

    if (const auto shortcut = button->shortcut(); !shortcut.isEmpty()) {
        return WidgetSequence {button, shortcut};
    }

    if constexpr (std::is_base_of_v<QToolButton, Button>) {
        if (auto action = button->defaultAction(); action && !action->shortcut().isEmpty()) {
            return WidgetSequence {button, action->shortcut()};
        } else if (auto menu = button->menu(); menu && !menu->menuAction()->shortcut().isEmpty()) {
            return WidgetSequence {button, menu->menuAction()->shortcut()};
        }
    }

    if constexpr (std::is_base_of_v<QPushButton, Button>) {
        if (auto menu = button->menu(); menu && !menu->menuAction()->shortcut().isEmpty()) {
            return WidgetSequence {button, menu->menuAction()->shortcut()};
        }
    }

    return {};
}

bool QKeySequenceRevealerFilter::eventFilter(QObject *object, QEvent *event) {
    switch (event->type()) {
    case QEvent::ToolTip:
    case QEvent::WhatsThis: {
        const auto widgetToolTip = [&]() -> std::optional<WidgetToolTip> {
            std::optional<WidgetSequence> ws;

            if (!ws) {
                ws = buttonEffectiveShortcut(qobject_cast<QToolButton *>(object));
            }

            if (!ws) {
                ws = buttonEffectiveShortcut(qobject_cast<QPushButton *>(object));
            }

            if (!ws) {
                if (auto label = qobject_cast<QLabel *>(object); label && !label->text().isEmpty()) {
                    const auto sequence = QKeySequence::mnemonic(label->text());

                    if (!sequence.isEmpty()) {
                        ws = {label, sequence};
                    }
                }
            }

            return ws
                ? WidgetToolTip {ws->first, QSL("%1 (%2)").arg(ws->first->toolTip(), ws->second.toString()).trimmed()}
                : std::optional<WidgetToolTip> {};
        }();

        if (widgetToolTip) {
            if (event->type() == QEvent::ToolTip) {
                const auto he = static_cast<QHelpEvent *>(event);
                QToolTip::showText(he->globalPos(), widgetToolTip->second, widgetToolTip->first);
            } else if (event->type() == QEvent::WhatsThis) {
                const auto he = static_cast<QHelpEvent *>(event);
                QWhatsThis::showText(he->globalPos(), widgetToolTip->second, widgetToolTip->first);
            }

            return true;
        }

        break;
    }
    default:
        break;
    }

    return QObject::eventFilter(object, event);
}
