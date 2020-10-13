import QtQuick 2.9
import QtQuick.Controls 2.2

import MuseScore.UiComponents 1.0
import MuseScore.Extensions 1.0

Item {
    id: root

    property string search: ""
    property string backgroundColor: ui.theme.backgroundPrimaryColor

    Component.onCompleted: {
        extensionListModel.load()
    }

    QtObject {
        id: privateProperties

        property string selectedExtensionViewType: "undefined" // "installed" "notinstalled"
        property int selectedExtensionIndex: -1
        property var selectedExtension: undefined

        function resetSelectedExtension() {
            selectedExtensionIndex = -1
            selectedExtensionViewType = "undefined"
            selectedExtension = undefined
        }
    }

    ExtensionListModel {
        id: extensionListModel

        onProgress: {
            extensionPanel.setProgress(status, indeterminate, current, total)
        }
        onFinish: {
            privateProperties.selectedExtension = item
            extensionPanel.resetProgress()
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: flickable.top

        height: 8
        z: 1

        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: root.backgroundColor
            }
            GradientStop {
                position: 1.0
                color: "transparent"
            }
        }
    }

    Flickable {
        id: flickable

        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 133
        anchors.right: parent.right
        anchors.rightMargin: 133
        anchors.bottom: extensionPanel.visible ? extensionPanel.top : parent.bottom

        clip: true

        contentWidth: width
        contentHeight: extensionsColumn.height
        interactive: height < contentHeight

        ScrollBar.vertical: StyledScrollBar {
            parent: flickable.parent

            anchors.top: parent.top
            anchors.bottom: extensionPanel.visible ? extensionPanel.top : parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: 16

            visible: flickable.contentHeight > flickable.height
            z: 1
        }

        Column {
            id: extensionsColumn

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            spacing: 20

            ExtensionsListView {
                id: installedView

                anchors.left: parent.left
                anchors.right: parent.right

                title: qsTrc("extensions", "Installed")

                model: extensionListModel
                visible: count > 0

                selectedIndex: {
                    return privateProperties.selectedExtensionViewType === "installed" ?
                           privateProperties.selectedExtensionIndex : -1
                }

                filters: [
                    FilterValue {
                        roleName: "name"
                        roleValue: root.search
                        compareType: CompareType.Contains
                    },
                    FilterValue {
                        roleName: "status"
                        roleValue: ExtensionStatus.Installed
                        compareType: CompareType.Equal
                    }
                ]

                onClicked: {
                    privateProperties.selectedExtensionViewType = "installed"
                    privateProperties.selectedExtensionIndex = index
                    privateProperties.selectedExtension = extensionListModel.extension(index)

                    extensionPanel.open()
                }
            }

            ExtensionsListView {
                id: notInstalledView

                anchors.left: parent.left
                anchors.right: parent.right

                title: qsTrc("extensions", "Not Installed")

                model: extensionListModel
                visible: count > 0

                selectedIndex: {
                    return privateProperties.selectedExtensionViewType === "notinstalled" ?
                           privateProperties.selectedExtensionIndex : -1
                }

                filters: [
                    FilterValue {
                        roleName: "name"
                        roleValue: root.search
                        compareType: CompareType.Contains
                    },
                    FilterValue {
                        roleName: "status"
                        roleValue: ExtensionStatus.NoInstalled
                        compareType: CompareType.Equal
                    }
                ]

                onClicked: {
                    privateProperties.selectedExtensionViewType = "notinstalled"
                    privateProperties.selectedExtensionIndex = index
                    privateProperties.selectedExtension = extension

                    extensionPanel.open()
                }
            }
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: flickable.bottom

        visible: !extensionPanel.visible
        height: 8
        z: 1

        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "transparent"
            }
            GradientStop {
                position: 1.0
                color: root.backgroundColor
            }
        }
    }

    onSearchChanged: {
        extensionPanel.close()
    }

    InstallationPanel {
        id: extensionPanel

        property alias selectedExtension: privateProperties.selectedExtension

        title: Boolean(selectedExtension) ? selectedExtension.name : ""
        description: Boolean(selectedExtension) ? selectedExtension.description : ""
        installed: Boolean(selectedExtension) ? (selectedExtension.status === ExtensionStatus.Installed ||
                                                 selectedExtension.status === ExtensionStatus.NeedUpdate) : false
        hasUpdate: Boolean(selectedExtension) ? (selectedExtension.status === ExtensionStatus.NeedUpdate) : false
        neutralButtonTitle: qsTrc("languages", "View full description")
        background: flickable

        additionalInfoModel: [
            {"title": qsTrc("languages", "Author:"), "value": qsTrc("languages", "MuseScore")},
            {"title": qsTrc("languages", "Maintained by:"), "value": qsTrc("languages", "MuseScore")}
        ]

        onInstallRequested: {
            Qt.callLater(extensionListModel.install, selectedExtension.code)
        }

        onUpdateRequested: {
            Qt.callLater(extensionListModel.update, selectedExtension.code)
        }

        onUninstallRequested: {
            Qt.callLater(extensionListModel.uninstall, selectedExtension.code)
        }

        onNeutralButtonClicked: {
            Qt.callLater(extensionListModel.openFullDescription, selectedExtension.code)
        }

        onClosed: {
            privateProperties.resetSelectedExtension()
        }
    }
}
