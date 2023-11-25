#ifndef VTABLEWIDGET_H
#define VTABLEWIDGET_H

#include <QWidget>
#include <QHeaderView>

namespace Ui {
    class vTableWidget;
}

class vTableWidget : public QWidget
{
    Q_OBJECT


public:
    enum RowPerPage{
        _10,
        _20,
        _50,
        _100
    };
    Q_ENUM(RowPerPage);
    vTableWidget(QWidget *parent = 0);
    ~vTableWidget();

    const QStringList &verticalHeader() const;
    void setVerticalHeader(const QStringList &newVerticalHeader);


    const QStringList &horizontalHeader() const;
    void setHorizontalHeader(const QStringList &newHorizontalHeader);


    int rowCount() const;
    void setRowCount(int newRowCount);

    int columnCount() const;
    void setColumnCount(int newColumnCount);


    const RowPerPage &rowPerPage() const;
    void setRowPerPage(const RowPerPage &newRowPerPage);

    const QList<QStringList> &datasource() const;
    void setDatasource(const QList<QStringList> &newDatasource);
    void setDatasource(const QList<QVariantList> &newVariantDatasource);

    bool pagination() const;
    void setPagination(bool newPagination);

    bool stretchLastSection() const;
    void setStretchLastSection(bool state);

    QHeaderView::ResizeMode hResizeMode() const;
    void setHResizeMode(QHeaderView::ResizeMode newHResizeMode);

    bool alternateRowColor() const;
    void setAlternateRowColor(bool newAlternateRowColor);

    const QColor &alternateColor() const;
    void setAlternateColor(const QColor &newAlternateColor);



    const QString &dateFormat() const;
    void setDateFormat(const QString &newDateFormat);

    int decimal() const;
    void setDecimal(int newDecimal);

signals:
    void gridChanged();
    void datasourceChanged();


    void rowPerPageChanged();

    void paginationChanged();

    void hResizeModeChanged();

    void alternateRowColorChanged();

    void alternateColorChanged();

    void dateFormatChanged();

    void decimalChanged();

private slots:

    void on_btnFirst_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

    void on_btnLast_clicked();

    void on_cmbRowPerPage_currentIndexChanged(int index);

    void on_spnPageNumber_editingFinished();

private:
    Ui::vTableWidget *ui;
    QStringList _verticalHeader;
    QStringList _horizontalHeader;
    int _rowCount;
    int _columnCount;

    QList<QStringList> _datasource;

    RowPerPage _rowPerPage;
    int _rowsPerPageCount[4] = {10, 20, 50, 100};

    int _totalPage;
    int _currentPage;
    QList<int> _boolColumns;
    QHeaderView::ResizeMode _hResizeMode;

    bool _alternateRowColor;
    QColor _alternateColor;

    QString _dateFormat;
    int _decimal;

    Q_PROPERTY(QStringList verticalHeader READ verticalHeader WRITE setVerticalHeader NOTIFY gridChanged)
    Q_PROPERTY(QStringList horizontalHeader READ horizontalHeader WRITE setHorizontalHeader NOTIFY gridChanged)
    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount NOTIFY gridChanged)
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY gridChanged)
    Q_PROPERTY(RowPerPage rowPerPage READ rowPerPage WRITE setRowPerPage NOTIFY rowPerPageChanged)
    Q_PROPERTY(bool pagination READ pagination WRITE setPagination NOTIFY paginationChanged)
    Q_PROPERTY(bool stretchLastSection READ stretchLastSection WRITE setStretchLastSection)
    Q_PROPERTY(QHeaderView::ResizeMode horizontalResizeMode READ hResizeMode WRITE setHResizeMode NOTIFY hResizeModeChanged)
    Q_PROPERTY(bool alternateRowColor READ alternateRowColor WRITE setAlternateRowColor NOTIFY alternateRowColorChanged)
    Q_PROPERTY(QColor alternateColor READ alternateColor WRITE setAlternateColor NOTIFY alternateColorChanged)

private: //methods
    void loadData();
    int rowsPerPageCount();
    void reloadData();

    Q_PROPERTY(QString dateFormat READ dateFormat WRITE setDateFormat NOTIFY dateFormatChanged)
    Q_PROPERTY(int decimal READ decimal WRITE setDecimal NOTIFY decimalChanged)
};

#endif // VTABLEWIDGET_H
