#include "gvimage.h"


GVImage::GVImage()
{
    m_dTheta = 0;
    m_dPhi = 0;
}

GVImage::GVImage(char* p_cFilename)
{
    m_dTheta = 0;
    m_dPhi = 0;
    openFile(p_cFilename);
}

GVImage::~GVImage()
{
    //TODO: Faire le menage
}

int GVImage::openFile(char* p_cFilename)
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
        m_p_ucImageData = new unsigned char[4 * m_iSideLenght * m_iSideLenght * NUMBER_OF_CHANNELS];

        //CENTER POINT
        m_iCenterPointX = (*m_p_iImageWidth)/2;
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

        //SET SIZE OF ARRAY TO 0 BACAUSE NEW READING
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

        unsigned char ucRedArr[8];
        unsigned char ucGreenArr[8];
        unsigned char ucBlueArr[8];

        //READ MAP AND PIXELS FOR NUMBER OF MAPS IN LEVEL 0
        for(int i = 0; i < m_iArrCubeAtLevel[0]; i++)
        {
            //COPY REFERENCE OF EACH CUBE IN ARRAY M_P_GVIMAGEARRAY
            m_p_GVImageArray[iWritingNextCubeIndex] = new GVIndexCube(&*m_p_iImageWidth,
                                                                      &*m_p_iImageHeight,
                                                                      &*m_p_ucImageData,
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
            m_p_GVImageArray[iWritingNextCubeIndex]->addPixelsCube(iWritingNextCubeIndex,
                                                                   ucMap,
                                                                   ucRedArr,
                                                                   ucGreenArr,
                                                                   ucBlueArr);
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
    //INITIALLY FILL THE IMAGE IN BLACK
    for(int i = 0; i < (*m_p_iImageWidth)*(*m_p_iImageHeight)*3; i++)
    {
        m_p_ucImageData[i] = 0;
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
                             (double)m_iCenterPointY);
}

/*

GVImage::GVImage()
{
}

GVImage::GVImage(char* fileName)
{
    openFile(fileName);
}

void GVImage::openFile(char* fileName)
{
    fstream file;
    file.open(fileName);

    if(file.is_open()){

        cout<<endl<<"File Opened"<<endl;

        //Cube Description
        file >> m_cubeWidth >> m_cubeHeight >> m_cubeDepth;
        file >> m_nonEmpty8x8x8Cube;

        //Reading Check-Up
        cout<<"-------------------------------"<<endl;
        cout<<"Dimensions: "<<m_cubeWidth<<"x"<<m_cubeHeight<<"x"<<m_cubeDepth<<endl;
        cout<<"Cubes non vides: "<<m_nonEmpty8x8x8Cube<<endl;
        cout<<"-------------------------------"<<endl;

        //Index dimensions calculations
        m_indexWidth = m_cubeWidth / 8;
        m_indexHeight = m_cubeHeight / 8;
        m_indexDepth = m_cubeDepth / 8;

        //Memory allocation
        m_8x8x8CubeIndexArray = new unsigned long [m_nonEmpty8x8x8Cube];
        m_8x8x8InternalBoolIndex = new bool [m_nonEmpty8x8x8Cube * 512];

        //8x8x8 Cube Index Reading
        for(int i = 0; i < m_nonEmpty8x8x8Cube; i++)
        {
            file>>m_8x8x8CubeIndexArray[i];
        }

        //Internal Map Reading
        int internalMapBuffer = 0;
        int numOfPixel = 0;
        for(int i = 0; i < m_nonEmpty8x8x8Cube * 512; i++)
        {
            file >> internalMapBuffer;

            if(internalMapBuffer == 0){
                m_8x8x8InternalBoolIndex[i] = 0;
            }
            else{
                numOfPixel++;
                m_8x8x8InternalBoolIndex[i] = 1;
            }
        }

        //Reading Pixels Data
        //TODO: Change int to char(when binary)
        m_pixelsData = new unsigned int[numOfPixel*m_nonEmpty8x8x8Cube*3];
        cout<<"DataSize = "<<numOfPixel*m_nonEmpty8x8x8Cube*3<<endl;

        //Lecture des données
        for(int i = 0; i < numOfPixel*m_nonEmpty8x8x8Cube*3; i++)
        {
            file >> m_pixelsData[i];
        }

        //Closing File
        file.close();
    }
}

void GVImage::generateImage(unsigned char pixels[], int width, int height)
{
    //64*3 = 192
    int tmpArray[192];

    //Fill unused in black
    for(int i = 0;  i < width* height*3 ;i++)
    {
        if(i < 192)
        {
            tmpArray[i] = 0;
        }
        pixels[i] = 0;
    }

    int offsetPixelsArray = 0;
    //Remove 1 dimension
    for(int j = 0; j < 8; j++)//height
    {
        for(int i = 0 ; i < 8; i++)//width
        {
            for(int c = 0; c < 3; c++)
            {
                if(m_8x8x8InternalBoolIndex[(i + 8*j)] == 1)
                {
                    //pixel assignation
                    tmpArray[c + 3*(i + (8*j))] = m_pixelsData[offsetPixelsArray];
                    offsetPixelsArray ++;
                }
            }
        }
    }
    //TODO: fill final image in one loop
    for(int i = 0;  i < (int)(width/8); i++)
    {
        for(int j = 0; j < (int)(height/8); j++)
        {
            //if()
            {
                for(int a= 0; a < 8; a++)
                {
                    for(int b = 0; b < 8; b++)
                    {
                        for(int c = 0; c < 3; c++)
                        {
                            pixels[((i*8) + a+ (j*8*width) + (b*width))*3 + c] = tmpArray[c + 3*(a + (8*b))];
                        }
                    }
                }
            }
        }
    }

    /*int offsetPixelsArray = 0;

    int offsetWidth = 0;
    int offsetHeight = 0;
    int offsetDepth = 0;
    int rest;

    int currentCube = 0; //increment in a for loop evnetually

    for(int d = 0; d < 8; d++)//depth
    {
        for(int j = 0; j < 8; j++)//height
        {
            for(int i = 0 ; i < 8; i++)//width
            {
                if(m_8x8x8InternalBoolIndex[(i + 8*j + 64*d) * (currentCube+1)] == 1)//Pixel existe
                {
                    for(int c = 0; c < 3; c++)
                    {
                        if(m_8x8x8CubeIndexArray[currentCube] < m_indexWidth)
                        {
                            //MATH: OK!
                            offsetWidth = m_8x8x8CubeIndexArray[currentCube];
                        }
                        else if((m_8x8x8CubeIndexArray[currentCube]/m_indexWidth) < m_indexHeight)
                        {
                            //MATH: OK!
                            offsetHeight = m_8x8x8CubeIndexArray[currentCube]/m_indexWidth;
                            offsetWidth = m_8x8x8CubeIndexArray[currentCube]%m_indexWidth;

                        }
                        else
                        {
                            //MATH: OK!
                            offsetDepth = m_8x8x8CubeIndexArray[currentCube]/(m_indexHeight*m_indexHeight);
                            rest = m_8x8x8CubeIndexArray[currentCube]%(m_indexHeight*m_indexHeight);
                            offsetHeight = rest/m_indexWidth;
                            offsetWidth = rest%m_indexWidth;
                        }

                        //pixel assignation
                        pixels[c + 3*((i+offsetWidth*8) + ((8*j)+offsetDepth*8))] = m_pixelsData[offsetPixelsArray];
                        offsetPixelsArray ++;
                    }
                }
            }
        }
    }
}


*/
