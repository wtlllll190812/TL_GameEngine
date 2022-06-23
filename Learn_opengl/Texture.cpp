#include"Texture.h"

Texture::Texture(std::string path)
{
	glGenTextures(1, &texture);//�趨��������,���洢����
	glBindTexture(GL_TEXTURE_2D, texture);//������
	 // Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);//��������(����Ŀ��,ָ��mipmap����,�洢��ʽ,���,�߶�,0,ԭͼ��ʽ,��������)
	glGenerateMipmap(GL_TEXTURE_2D);//����mipmap
	SOIL_free_image_data(image);//�ͷ��ڴ�
	glBindTexture(GL_TEXTURE_2D, 0);//���
}

Texture::~Texture()
{
}