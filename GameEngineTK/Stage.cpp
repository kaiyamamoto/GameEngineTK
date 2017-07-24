#include "pch.h"
#include "Stage.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "PlayerRobot.h"
#include "EnemyRobot.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

// �ÓI�ϐ��錾
// ��؂�L��
const wchar_t Stage::DELIMITA = L',';
const int Stage::MAP_SIZE_X = 10;
const int Stage::MAP_SIZE_Y = 10;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="filePath">�t�@�C���̃p�X</param>
Stage::Stage(const wchar_t* filePath)
	:m_filePath(filePath)
{
}

/// <summary>
/// �t�@�C���̓ǂݍ���
/// </summary>
void Stage::Load()
{
	wifstream ifs(m_filePath);
	wstring line;

	// 1�s�X�L�b�v
	getline(ifs, line);
	// ���f��path�f�[�^�ǂݍ���
	LoadModel(&ifs);
	// 1�s�X�L�b�v
	getline(ifs, line);
	// �}�b�v�f�[�^�ǂݍ���
	LoadMap(&ifs);
}

/// <summary>
/// �쐬
/// </summary>
/// <param name="fileName">�t�@�C���̃p�X</param>
/// <param name="interval">�Ԋu</param>
/// <returns>�쐬�̐������s</returns>
bool Stage::Create(const float interval)
{
	// vector������
	m_pLandShapeArray.clear();

	// �쐬
	for (int i = 0; i < MAP_SIZE_Y; i++){
		for (int j = 0; j < MAP_SIZE_X; j++){
			// ���f���쐬
			std::auto_ptr<LandShape> landshape(new LandShape());

			StageObjectData* data = m_objData[m_map[i][j]].get();

			// �ǂݍ���
			const wchar_t* path = data->path.c_str();
			landshape->Initialize(path, path);

			// �X�P�[�����f
			landshape->SetScale(data->scale);

			// ����]���f
			Vector3 rot = landshape->GetEulerAngle();
			rot.y = data->rotateY;
			landshape->SetEulerAngle(rot);

			// ���C�g����
			landshape->DisableLighting();

			// ���W
			landshape->SetPosition(Vector3(static_cast<float>(j)*interval, 0.0f, static_cast<float>(i)*interval));
			landshape->Update();
			// �R���e�i�ɒǉ�
			m_pLandShapeArray.push_back(std::move(landshape));
		}
	}
	return true;
}

void Stage::Draw(const DirectX::CommonStates & state, const DirectX::SimpleMath::Matrix & view, const DirectX::SimpleMath::Matrix & proj)
{
	// �n�`�̕`��
	for (auto itr = m_pLandShapeArray.begin(); itr != m_pLandShapeArray.end(); ++itr) {
		(*itr)->Draw(state, view, proj);
	}
}

/// <summary>
/// �j��
/// </summary>
void Stage::Delete()
{
	// ���[�J����vector�@�֐����o���������
	std::vector<std::shared_ptr<LandShape>>array;
	// swap �œ���ւ���
	m_pLandShapeArray.swap(array);
	// ���[�J����vector�͎����I�ɔj�������
}

/// <summary>
/// ���f��path�̓ǂݍ���
/// </summary>
/// <param name="file">�ǂݍ��ݒ��̃t�@�C��</param>
void Stage::LoadModel(wifstream* file)
{
	wstring line;

	// ���f���̐��擾
	getline(*file, line);
	m_modelNum = stoi(line.c_str());

	// Path���X�g�̃T�C�Y����
	m_objData.resize(m_modelNum);

	// �e�s�̃f�[�^�����
	for (int i = 0; i < m_modelNum; i++) {
		// ���f��
		wstring fileName;
		wstring arrayNumStr;

		// ��s�ǂݍ���
		getline(*file, line);

		// 1�s���𕶎���X�g���[���ɕϊ�
		wstringstream stream(line);

		// �t�@�C�����̕������ǂݍ���
		getline(stream, fileName, DELIMITA);

		// �v�f�ԍ��ǂݎ��
		getline(stream, arrayNumStr, DELIMITA);
		int arrayNum;
		arrayNum = stoi(arrayNumStr.c_str());

		// �f�[�^�쐬
		m_objData[arrayNum] = make_unique<StageObjectData>();

		// �X�P�[���ǂݎ��
		getline(stream, arrayNumStr, DELIMITA);
		float scale = static_cast<float>(stod(arrayNumStr.c_str()));
		m_objData[arrayNum]->scale = scale;

		// y��]�ǂݎ��
		getline(stream, arrayNumStr, DELIMITA);
		float rotY = static_cast<float>(stod(arrayNumStr.c_str()));
		m_objData[arrayNum]->rotateY = rotY;

		// Path���X�g�ɒǉ�
		m_objData[arrayNum]->path = fileName;
	}
}

/// <summary>
/// �}�b�v�f�[�^�̓ǂݍ���
/// </summary>
/// <param name="file">�ǂݍ��ݒ��̃t�@�C��</param>
void Stage::LoadMap(wifstream* file)
{
	//�f�[�^�ǂݍ��ݗp
	wstring str;
	int data[MAP_SIZE_X * MAP_SIZE_Y];
	wstring token;

	int dataCnt = 0;

	//csv�̃f�[�^���J���}���΂��ēǂݍ���
	for (int i = 0; i < MAP_SIZE_Y; i++) {
		getline(*file, str);
		wstringstream stream(str);
		for (int j = 0; j < MAP_SIZE_X; j++) {
			getline(stream, token, DELIMITA);
			data[dataCnt] = stoi(token.c_str());
			dataCnt++;
		}
	}
	// �f�[�^����
	dataCnt = 0;
	// �z��m��
	m_map = vector<vector<int>>(MAP_SIZE_Y, vector<int>(MAP_SIZE_X));
	for (int i = 0; i < MAP_SIZE_Y; i++) {
		for (int j = 0; j < MAP_SIZE_X; j++) {
			// �f�[�^����
			m_map[i][j] = data[dataCnt];
			dataCnt++;
		}
	}
	return;
}
