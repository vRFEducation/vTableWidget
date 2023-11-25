#include "vTableWidget.h"
#include "ui_vTableWidget.h"
#include <QDateTime>

vTableWidget::vTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vTableWidget),
    _totalPage(0),
    _alternateColor(QColor(204, 204, 204)),
    _dateFormat("yyyy/MM/dd"),
    _decimal(2)

{
    ui->setupUi(this);

}

vTableWidget::~vTableWidget()
{
    delete ui;
}

const QStringList &vTableWidget::verticalHeader() const
{
    return _verticalHeader;
}

void vTableWidget::setVerticalHeader(const QStringList &newVerticalHeader)
{
    if (_verticalHeader == newVerticalHeader)
        return;
    _verticalHeader = newVerticalHeader;
    setRowCount(_verticalHeader.length());
    ui->tbl->setVerticalHeaderLabels(_verticalHeader);
}

const QStringList &vTableWidget::horizontalHeader() const
{
    return _horizontalHeader;
}

void vTableWidget::setHorizontalHeader(const QStringList &newHorizontalHeader)
{
    if (_horizontalHeader == newHorizontalHeader)
        return;
    _horizontalHeader = newHorizontalHeader;
    setColumnCount(_horizontalHeader.length());
    ui->tbl->setHorizontalHeaderLabels(_horizontalHeader);

}

int vTableWidget::rowCount() const
{
    return ui->tbl->rowCount();
}

void vTableWidget::setRowCount(int newRowCount)
{
    if (rowCount() == newRowCount)
        return;

//    int index = ui->cmbRowPerPage->currentIndex();
//    int rowPerPage = (index * 25 > 0)? index * 25: 10;

//    int count = (rowCount() < rowPerPage) ? rowCount() : row
    ui->tbl->setRowCount(newRowCount);

}

int vTableWidget::columnCount() const
{
    return ui->tbl->columnCount();
}

void vTableWidget::setColumnCount(int newColumnCount)
{
    if (columnCount() == newColumnCount)
        return;
    ui->tbl->setColumnCount(newColumnCount);

}




void vTableWidget::on_btnFirst_clicked()
{
    _currentPage = 0;
    loadData();
}


void vTableWidget::on_btnPrevious_clicked()
{
    if (_currentPage > 0) {
        _currentPage--;
        loadData();
    }
}


void vTableWidget::on_btnNext_clicked()
{
    if (_currentPage + 1 < _totalPage) {
        _currentPage++;
        loadData();
    }
}


void vTableWidget::on_btnLast_clicked()
{
    _currentPage = _totalPage - 1;
    loadData();
}

const vTableWidget::RowPerPage &vTableWidget::rowPerPage() const
{
    return _rowPerPage;
}

void vTableWidget::setRowPerPage(const RowPerPage &newRowPerPage)
{
    if (_rowPerPage == newRowPerPage)
        return;
    _rowPerPage = newRowPerPage;
    ui->cmbRowPerPage->setCurrentIndex(newRowPerPage);
    reloadData();
    emit rowPerPageChanged();
}

void vTableWidget::on_cmbRowPerPage_currentIndexChanged(int index)
{
    _rowPerPage = (RowPerPage)index;
    reloadData();
    emit rowPerPageChanged();

}

bool vTableWidget::pagination() const
{
    return ui->wdgPagination->isVisible();
}

void vTableWidget::setPagination(bool newPagination)
{
    ui->wdgPagination->setVisible(newPagination);
    emit paginationChanged();
}

bool vTableWidget::stretchLastSection() const
{
    return ui->tbl->horizontalHeader()->stretchLastSection();
}

void vTableWidget::setStretchLastSection(bool state)
{
    ui->tbl->horizontalHeader()->setStretchLastSection(state);
}

const QList<QStringList> &vTableWidget::datasource() const
{
    return _datasource;
}


void vTableWidget::setDatasource(const QList<QStringList> &newDatasource)
{
    if (_datasource == newDatasource)
        return;
    _datasource = newDatasource;
    reloadData();

    emit datasourceChanged();
}

void vTableWidget::loadData()
{
    if (_datasource.length() == 0) {
        return;
    }

    int start = 0;
    int end = 0;
    if (!pagination()) {
        start = 0;
        end = _datasource.length();
    } else {
        int rowPerPage = rowsPerPageCount();
        start = _currentPage * rowPerPage;
        end = (_currentPage + 1) * rowPerPage;
        if (end >= _datasource.length()) {
            end = _datasource.length();
        }
    }

    ui->tbl->clear();
    ui->tbl->setRowCount(end - start);

    for (int r = start; r < end; ++r) {
        auto row = _datasource[r];
        if (row.length() > ui->tbl->columnCount()) {
            ui->tbl->setColumnCount(row.length());
        }
        for (int c = 0; c < row.length(); ++c) {
            auto item = new QTableWidgetItem(row[c]);
            if (_alternateRowColor && r % 2 == 1) {
                item->setBackground(_alternateColor);
            }
            if (_boolColumns.contains(c)) {
                item->setCheckState((row[c] == "True")? Qt::Checked : Qt::Unchecked);
                item->setText("");
            }
            ui->tbl->setItem(r - start, c, item);
        }
    }
    ui->spnPageNumber->setValue(_currentPage + 1);


}

int vTableWidget::rowsPerPageCount()
{
    return _rowsPerPageCount[ui->cmbRowPerPage->currentIndex()];
}

void vTableWidget::on_spnPageNumber_editingFinished()
{
    if(ui->spnPageNumber->value() == _currentPage + 1){
        return;
    }
    _currentPage = ui->spnPageNumber->value() - 1;
    loadData();
}

int vTableWidget::decimal() const
{
    return _decimal;
}

void vTableWidget::setDecimal(int newDecimal)
{
    if (_decimal == newDecimal)
        return;
    _decimal = newDecimal;
    emit decimalChanged();
}

const QString &vTableWidget::dateFormat() const
{
    return _dateFormat;
}

void vTableWidget::setDateFormat(const QString &newDateFormat)
{
    if (_dateFormat == newDateFormat)
        return;
    _dateFormat = newDateFormat;
    emit dateFormatChanged();
}



void vTableWidget::setDatasource(const QList<QVariantList> &newVariantDatasource)
{
    _datasource.clear();
    _boolColumns.clear();
    int columnIndex = 0;
    foreach (auto row, newVariantDatasource) {
        QStringList stringRow;
        columnIndex = 0;
        foreach (auto item, row) {
            switch (item.userType()) {
            case QMetaType::Bool:
                stringRow << ((item.toBool()) ? "True" : "False");
                _boolColumns << columnIndex;
                break;
            case QMetaType::QDate:
                stringRow << item.toDate().toString(_dateFormat);
                break;
            case QMetaType::QDateTime:
                stringRow << item.toDateTime().toString(_dateFormat);
                break;
            case QMetaType::Double:
                stringRow << QString::number(item.toDouble(), 'f', _decimal);
                break;
            case QMetaType::Float:
                stringRow << QString::number(item.toFloat(), 'f', _decimal);
                break;
            default:
                stringRow << item.toString();

                break;
            }
            columnIndex++;
        }
        _datasource.append(stringRow);
    }
    reloadData();
}

const QColor &vTableWidget::alternateColor() const
{
    return _alternateColor;
}

void vTableWidget::setAlternateColor(const QColor &newAlternateColor)
{
    if (_alternateColor == newAlternateColor)
        return;
    _alternateColor = newAlternateColor;
    emit alternateColorChanged();
}

bool vTableWidget::alternateRowColor() const
{
    return _alternateRowColor;
}

void vTableWidget::setAlternateRowColor(bool newAlternateRowColor)
{
    if (_alternateRowColor == newAlternateRowColor)
        return;
    _alternateRowColor = newAlternateRowColor;
    emit alternateRowColorChanged();
}

QHeaderView::ResizeMode vTableWidget::hResizeMode() const
{
    return _hResizeMode;
}

void vTableWidget::setHResizeMode(QHeaderView::ResizeMode newHResizeMode)
{
    if (_hResizeMode == newHResizeMode)
        return;
    _hResizeMode = newHResizeMode;
    ui->tbl->horizontalHeader()->setSectionResizeMode(_hResizeMode);
    emit hResizeModeChanged();
}

void vTableWidget::reloadData()
{
    _currentPage = 0;
    _totalPage = qCeil(1.0 * _datasource.length() / rowsPerPageCount());

    ui->spnPageNumber->setSuffix(QString("/ %1").arg(_totalPage));
    ui->spnPageNumber->setMaximum(_totalPage);
    loadData();
}

