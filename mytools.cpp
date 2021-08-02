#include "mytools.h"

MyTools::MyTools()
{

}

/**
 * @brief GernerateQRCode
 * 生成二维码函数
 * @param text  二维码内容
 * @param qrPixmap  二维码像素图
 * @param scale 二维码缩放比例
 */
void MyTools::GernerateQRCode(const QString &text, QPixmap &qrPixmap, int scale)
{
    if(text.isEmpty())
    {
        return;
    }

    //二维码数据
    QRcode *qrCode = nullptr;

    //这里二维码版本传入参数是2,实际上二维码生成后，它的版本是根据二维码内容来决定的
    //参数依次为:内容、二维码版本1-40,容错级别L、M、Q、H,编码模式,敏感事件
    qrCode = QRcode_encodeString(text.toStdString().c_str(), 2,QR_ECLEVEL_Q, QR_MODE_8, 1);

    if(nullptr == qrCode)
    {
        return;
    }

    int qrCode_Width = qrCode->width > 0 ? qrCode->width : 1;
    int width = scale * qrCode_Width;
    int height = scale * qrCode_Width;

    QImage image(width, height, QImage::Format_ARGB32_Premultiplied);

    QPainter painter(&image);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, width, height);
    QColor foreground(36,188,119);
    painter.setBrush(foreground);
    for(int y = 0; y < qrCode_Width; ++y)
    {
        for(int x = 0; x < qrCode_Width; ++x)
        {
            unsigned char character = qrCode->data[y * qrCode_Width + x];
            if(character & 0x01)
            {
               QRect rect(x * scale, y * scale, scale, scale);
               painter.drawRects(&rect, 1);
            }
        }
    }

    qrPixmap = QPixmap::fromImage(image);
    QRcode_free(qrCode);
}
