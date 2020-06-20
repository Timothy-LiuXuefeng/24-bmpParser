
#pragma warning(disable:4996)
#include "readbmp.h"

INT readBmp()
{
	delete[] bmpBuf; 
	bmpBuf = NULL; 
	std::ifstream fin(inputBmpName, std::ios::in | std::ios::binary); 
	if (!fin) return READ_FAILURE; 
	UINT8 buf8_1, buf8_2; 
	UINT16 buf16; 
	UINT32 bmpSize; //λͼ��С
	UINT32 dataPos;	//�������ݿ�ʼλ��
	UINT32 buf32; 
	UINT32 width, height; //λͼ��Ⱥ͸߶�

	//���鿪ͷ�����ֽ��Ƿ���'B''M'
	fin.read((CHAR*)&buf8_1, 1); 
	fin.read((CHAR*)&buf8_2, 1);
	if (fin.eof()) 
	{
		fin.close();  
		return NOT_TWENTY_FOUR_BITMAP;
	}
	if (!(buf8_1 == 'B' && buf8_2 == 'M')) 
	{
		fin.close();
		return NOT_TWENTY_FOUR_BITMAP;
	}

	//��ȡ�ļ���С
	fin.read((CHAR*)&bmpSize, sizeof(UINT32)); 
	if (fin.eof()) 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}
	
	//��ȡ���ص㿪ʼ��λ��
	fin.seekg(sizeof(UINT32), std::ios::cur);
	fin.read((CHAR*)&dataPos, sizeof(UINT32)); 
	if (fin.eof() || dataPos == 0)
	{
		fin.close();
		return BITMAP_DESTROYED;
	}

	//��ȡ��Ϣ���С
	fin.read((CHAR*)&buf32, sizeof(UINT32)); 
	if (fin.eof() || buf32 != 0x28) 
	{
		fin.close(); 
		return BITMAP_DESTROYED; 
	}

	//��ȡλͼ��Ⱥ͸߶�
	fin.read((CHAR*)&width, sizeof(UINT32)); 
	fin.read((CHAR*)&height, sizeof(UINT32)); 
	if (fin.eof()) 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}

	//��ȡ����Ϊ1
	fin.read((CHAR*)&buf16, sizeof(UINT16)); 
	if (fin.eof() || buf16 != 1) 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}

	//��ȡλͼ��λ����ӦΪ24
	fin.read((CHAR*)&buf16, sizeof(UINT16)); 
	if (fin.eof()) 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}
	if (buf16 != 24) 
	{
		fin.close();
		return NOT_TWENTY_FOUR_BITMAP;
	}

	//���仺���ڴ�
	try
	{
		bmpBuf = new UCHAR[bmpSize - dataPos + 2 * sizeof(UINT32) + 5];
	}
	catch (std::bad_alloc)
	{
		bmpBuf = NULL; 
		fin.close(); 
		if (bmpSize - dataPos + 2 * sizeof(UINT32) < 0) return BITMAP_DESTROYED; 
		return BITMAP_TOO_LARGE; 
	}

	//��λͼ��Ⱥ͸߶�д�뻺����
	UCHAR* tmp = bmpBuf; 
	memcpy((void*)tmp, (const void*)&width, sizeof(width)); 
	tmp += sizeof(width); 
	memcpy((void*)tmp, (const void*)&height, sizeof(height));
	tmp += sizeof(height); 

	//��λͼ������Ϣд�뻺����
	fin.read((CHAR*)tmp, bmpSize - dataPos); 
	if (fin.eof()) 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}

	//�ж��ļ��Ƿ��Ѿ�����
	fin.read((CHAR*)&buf8_1, 1); 
	/*if (!fin.eof()) return BITMAP_DESTROYED; 
	{
		fin.close();
		return BITMAP_DESTROYED;
	}*/
	fin.close(); 

	return READ_SUCCESS; 
}
