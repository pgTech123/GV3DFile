#include "gvimage.h"


GVImage::GVImage()
{
    m_dTheta = 0;
    m_dPhi = 0;
    m_pLookupTable = new gvLookUpTable();
}

GVImage::GVImage(const char* p_cFilename)
{
    m_dTheta = 0;
    m_dPhi = 0;
    m_pLookupTable = new gvLookUpTable();
    openFile(p_cFilename);
}

GVImage::~GVImage()
{
    //TODO: Faire le menage
}

int GVImage::openFile(const char* p_cFilename)
{

    cout << "Trying to reach file ... " << endl;

    fstream file;
    file.open(p_cFilename);

    if(file.is_open()){

        cout << "File Opened" << endl;

        //READ CUBE SIDE LENGHT
        file >> m_iSideLenght;
        if(m_iSideLenght <= 1)
        {
            m_iSideLenght = 0;
            return INVALID_CUBE_SIZE;
        }

        //VERIFY BASE 2
        if(!isBase2(m_iSideLenght))
        {
            m_iSideLenght = 0;
            return SIZE_NOT_BASE_2;
        }

        cout << "Side Lenght: " << m_iSideLenght << endl;

        //SET IMAGE DATA
        m_p_iImageWidth = new int(2*m_iSideLenght);
        m_p_iImageHeight = new int(2*m_iSideLenght);
        m_p_ucImageData = new unsigned char[(*m_p_iImageWidth) * (*m_p_iImageHeight) * NUMBER_OF_CHANNELS];
        m_p_bPixelFilled = new bool[(*m_p_iImageWidth) * (*m_p_iImageHeight)];

        //CENTER POINT
        m_iCenterPointX = (*m_p_iImageWidth)/2;     //OPTIMISATION POSSIBLE
        m_iCenterPointY = (*m_p_iImageHeight)/2;

        //UNROTATED CORNERS
        m_iUnrotatedCornerX[0] = m_iCenterPointX - m_iSideLenght/2;       //(optimisable by m_iSideLenght/2)
        m_iUnrotatedCornerY[0] = m_iCenterPointY + m_iSideLenght/2;
        m_iUnrotatedCornerZ[0] = m_iSideLenght/2;

        m_iUnrotatedCornerX[1] = m_iCenterPointX + m_iSideLenght/2;
        m_iUnrotatedCornerY[1] = m_iCenterPointY + m_iSideLenght/2;
        m_iUnrotatedCornerZ[1] = m_iSideLenght/2;

        m_iUnrotatedCornerX[2] = m_iCenterPointX + m_iSideLenght/2;
        m_iUnrotatedCornerY[2] = m_iCenterPointY - m_iSideLenght/2;
        m_iUnrotatedCornerZ[2] = m_iSideLenght/2;

        m_iUnrotatedCornerX[3] = m_iCenterPointX - m_iSideLenght/2;
        m_iUnrotatedCornerY[3] = m_iCenterPointY - m_iSideLenght/2;
        m_iUnrotatedCornerZ[3] = m_iSideLenght/2;

        m_iUnrotatedCornerX[4] = m_iCenterPointX - m_iSideLenght/2;
        m_iUnrotatedCornerY[4] = m_iCenterPointY + m_iSideLenght/2;
        m_iUnrotatedCornerZ[4] = -(m_iSideLenght/2);

        m_iUnrotatedCornerX[5] = m_iCenterPointX + m_iSideLenght/2;
        m_iUnrotatedCornerY[5] = m_iCenterPointY + m_iSideLenght/2;
        m_iUnrotatedCornerZ[5] = -(m_iSideLenght/2);

        m_iUnrotatedCornerX[6] = m_iCenterPointX + m_iSideLenght/2;
        m_iUnrotatedCornerY[6] = m_iCenterPointY - m_iSideLenght/2;
        m_iUnrotatedCornerZ[6] = -(m_iSideLenght/2);

        m_iUnrotatedCornerX[7] = m_iCenterPointX - m_iSideLenght/2;
        m_iUnrotatedCornerY[7] = m_iCenterPointY - m_iSideLenght/2;
        m_iUnrotatedCornerZ[7] = -(m_iSideLenght/2);

        //COMPUTE NUMBER OF LEVELS
        m_iNumberOfLevels = firstHighBit(m_iSideLenght);
        cout << "Number of Levels: " << m_iNumberOfLevels << endl;

        m_iArrCubeAtLevel = new int[m_iNumberOfLevels];

        //SET SIZE OF ARRAY TO 0 BECAUSE NEW READING
        m_iSizeOfGVImageArray = 0;

        //DECLARATION BUFFER
        int iBuffer = 0;

        //READ NUMBER OF MAP FOR EACH LEVEL
        for(int i = 0; i < m_iNumberOfLevels; i++)
        {
            file >> iBuffer;
            m_iArrCubeAtLevel[i] = iBuffer;
            m_iSizeOfGVImageArray += iBuffer;
        }
        cout << "Number of Cubes: " << m_iSizeOfGVImageArray << endl;

        //ALLOC GVIMAGEARRAY (ARRAY OF POINTER OF CUBES)
        m_p_GVImageArray = new GVIndexCube*[m_iSizeOfGVImageArray];

        int iWritingNextCubeIndex = 0;

        int ucRedArr[8];
        int ucGreenArr[8];
        int ucBlueArr[8];

        //READ MAP AND PIXELS FOR NUMBER OF MAPS IN LEVEL 0
        for(int i = 0; i < m_iArrCubeAtLevel[0]; i++)
        {
            //COPY REFERENCE OF EACH CUBE IN ARRAY M_P_GVIMAGEARRAY
            m_p_GVImageArray[iWritingNextCubeIndex] = new GVIndexCube(&*m_p_iImageWidth,
                                                                      &*m_p_iImageHeight,
                                                                      &*m_p_ucImageData,
                                                                      &*m_p_bPixelFilled,
                                                                      &m_p_GVImageArray[0]);

            file >> iBuffer;
            unsigned char ucMap = (unsigned char)iBuffer;
            int numberOfPixels = numberHighBits(iBuffer);
            if(numberOfPixels > 8)
            {
                return FILE_CORRUPTED;
            }
            cout << "Number of Pixels in Cube: " << numberOfPixels << endl;

            for(int j = 0; j < numberOfPixels; j++)
            {
                //PIXEL READING
                file >> ucRedArr[j];
                file >> ucGreenArr[j];
                file >> ucBlueArr[j];
            }
            //FILL CUBE
                // !!!!!!!!TO UNCOMMENT!!!!!!!!!!!
                /*m_p_GVImageArray[iWritingNextCubeIndex]->addPixelsCube(iWritingNextCubeIndex,
                                                                       ucMap,
                                                                       ucRedArr,
                                                                       ucGreenArr,
                                                                       ucBlueArr);*/
                //TO REMOVE: TEST PURPOSE ONLY!!!!!!!!!!!
                this->addPixelsCube(iWritingNextCubeIndex,
                                    ucMap,
                                    ucRedArr,
                                    ucGreenArr,
                                    ucBlueArr);
                //END TEST

            iWritingNextCubeIndex ++;
        }





        //TODO
        //READ MAP FOR EACH LEVEL FOR ALL THE OTHER LEVELS
        //LINK EACH CHILD TO ITS PARENT

        //CLOSING FILE
        file.close();

        return NO_ERRORS;
    }

    cout << "Unable to reach File" << endl;

    return UNABLE_TO_OPEN_FILE;
}

int GVImage::getWidth()
{
    return *m_p_iImageWidth;
}

int GVImage::getHeight()
{
    return *m_p_iImageHeight;
}

unsigned char* GVImage::getData()
{
    return m_p_ucImageData;
}

void GVImage::setRotation(double dTheta, double dPhi)
{
    m_dTheta = dTheta;
    m_dPhi = dPhi;
}

void GVImage::generateImage()
{
    //INITIALLY EVERY PIXEL IS EMPTY
    for(int i = 0; i < (*m_p_iImageWidth)*(*m_p_iImageHeight); i++)
    {
        m_p_bPixelFilled[i] = false;
    }

    //COMPUTE EACH CORNER
    for(int i = 0; i < 8; i++)
    {
        m_dScreenRotatedCornerX[i] = computePosXOnScreen(m_iUnrotatedCornerX[i],
                                                         m_iUnrotatedCornerY[i],
                                                         m_iUnrotatedCornerZ[i],
                                                         m_dTheta,
                                                         m_dPhi);
        m_dScreenRotatedCornerY[i] = computePosYOnScreen(m_iUnrotatedCornerX[i],
                                                         m_iUnrotatedCornerY[i],
                                                         m_iUnrotatedCornerZ[i],
                                                         m_dTheta,
                                                         m_dPhi);
        m_dDstFromScreenRotated[i] = -1 * computeRotationZ(m_iUnrotatedCornerX[i],  //To respect axis
                                                      m_iUnrotatedCornerY[i],
                                                      m_iUnrotatedCornerZ[i],
                                                      m_dTheta,
                                                      m_dPhi);
    }

    //ORDER POINTS (Z AXIS) (SORT BY DST)
    sort(m_dDstFromScreenRotated ,m_dCornerSortedByDst);

    //APPLY ROTATION AND RENDER ON CHILDREN
    ApplyRotation_and_Render(m_dScreenRotatedCornerX,
                             m_dScreenRotatedCornerY,
                             m_dCornerSortedByDst,
                             (double)m_iCenterPointX,
                             (double)m_iCenterPointY,
                             m_pLookupTable);

    //FILL ALL EMPTY PIXELS IN BLACK
    for(int i = 0; i < (*m_p_iImageWidth)*(*m_p_iImageHeight); i++)
    {
        if(m_p_bPixelFilled[i] == false)
        {
            m_p_ucImageData[3*i] = 0;
            m_p_ucImageData[(3*i) + 1] = 0;
            m_p_ucImageData[(3*i) + 2] = 0;
        }
    }
}

