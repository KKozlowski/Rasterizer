#include "Mesh.h"
#include <sstream>
#include <stdio.h>
#include <iterator>
#include <iostream>
#include <corecrt_math_defines.h>

using namespace std;

Mesh::~Mesh()
{

}

Mesh Mesh::Cube()
{
	Mesh m;
	vector<Float4> v{
		{0,0,0},
		{-0.5f,  -0.5f,  -0.5f},
		{-0.5f,  -0.5f,  0.5f},
		{-0.5f,  0.5f,  -0.5f},
		{-0.5f,  0.5f,  0.5f},
		{0.5f,  -0.5f,  -0.5f},
		{0.5f,  -0.5f,  0.5f},
		{0.5f,  0.5f,  -0.5f},
		{0.5f,  0.5f,  0.5f}
	};

	vector<Float4> vn {
		{ 0,0,0 },
		{ 0.0f, 0.0f, 1.0f}, 
		{0.0f,  0.0f, -1.0f,},
		{0.0f,  1.0f,  0.0f,},
		{0.0f, -1.0f,  0.0f,},
		{1.0f,  0.0f,  0.0f,},
		{-1.0f,  0.0f,  0.0f,}
	};

	m.triangles = vector<Triangle *>{
		new Triangle(new Vertex(v[1], vn[2]), new Vertex(v[7], vn[2]), new Vertex(v[5], vn[2])),
		new Triangle(new Vertex(v[1], vn[2]), new Vertex(v[3], vn[2]), new Vertex(v[7], vn[2])),
		new Triangle(new Vertex(v[1], vn[6]), new Vertex(v[4], vn[6]), new Vertex(v[3], vn[6])),
		new Triangle(new Vertex(v[1], vn[6]), new Vertex(v[2], vn[6]), new Vertex(v[4], vn[6])),
		new Triangle(new Vertex(v[3], vn[3]), new Vertex(v[8], vn[3]), new Vertex(v[7], vn[3])),
		new Triangle(new Vertex(v[3], vn[3]), new Vertex(v[4], vn[3]), new Vertex(v[8], vn[3])),
		new Triangle(new Vertex(v[5], vn[5]), new Vertex(v[7], vn[5]), new Vertex(v[8], vn[5])),
		new Triangle(new Vertex(v[5], vn[5]), new Vertex(v[8], vn[5]), new Vertex(v[6], vn[5])),
		new Triangle(new Vertex(v[1], vn[4]), new Vertex(v[5], vn[4]), new Vertex(v[6], vn[4])),
		new Triangle(new Vertex(v[1], vn[4]), new Vertex(v[6], vn[4]), new Vertex(v[2], vn[4])),
		new Triangle(new Vertex(v[2], vn[1]), new Vertex(v[6], vn[1]), new Vertex(v[8], vn[1])),
		new Triangle(new Vertex(v[2], vn[1]), new Vertex(v[8], vn[1]), new Vertex(v[4], vn[1]))
	};

	for (Triangle *t : m.triangles)
	{
		t->a->col = Color::GetRandom();
		m.vertices.push_back(t->a);
		t->b->col = Color::GetRandom();
		m.vertices.push_back(t->b);
		t->c->col = Color::GetRandom();
		m.vertices.push_back(t->c);
	}

	return m;
}

void Mesh::release()
{
	for (std::vector< Triangle * >::iterator it = triangles.begin(); it != triangles.end(); ++it)
	{
		delete (*it);
	}
	triangles.clear();
	for (std::vector< Vertex * >::iterator it = vertices.begin(); it != vertices.end(); ++it)
	{
		delete (*it);
	}
	vertices.clear();
}

Mesh Mesh::Cylinder()
{
	Mesh m;
	vector<Float4> v {
		{ 0,0,0 },
		{0.000000f, -0.000000f, -1.000000f},
		{0.195090f, -0.000000f, -0.980785f},
		{0.382683f, -0.000000f, -0.923880f},
		{0.555570f, -0.000000f, -0.831470f},
		{0.707107f, -0.000000f, -0.707107f},
		{0.831470f, -0.000000f, -0.555570f},
		{0.923880f, -0.000000f, -0.382683f},
		{0.980785f, -0.000000f, -0.195090f},
		{1.000000f, -0.000000f, -0.000000f},
		{0.980785f, 0.000000f,  0.195090f },
		{0.923880f, 0.000000f,  0.382683f },
		{0.831470f, 0.000000f,  0.555570f },
		{0.707107f, 0.000000f,  0.707107f },
		{0.555570f, 0.000000f,  0.831470f },
		{0.382683f, 0.000000f,  0.923880f },
		{0.195090f, 0.000000f,  0.980785f },
		{-0.000000f, 0.000000f, 1.000000f},
		{-0.195091f, 0.000000f, 0.980785f},
		{-0.382684f, 0.000000f, 0.923879f},
		{-0.555571f, 0.000000f, 0.831469f},
		{-0.707107f, 0.000000f, 0.707106f},
		{-0.831470f, 0.000000f, 0.555570f},
		{-0.923880f, 0.000000f, 0.382683f},
		{-0.980785f, 0.000000f, 0.195089f},
		{-1.000000f, - 0.000000f, - 0.000001f},
		{-0.980785f, - 0.000000f, - 0.195091f},
		{-0.923879f, - 0.000000f, - 0.382684f},
		{-0.831469f, - 0.000000f, - 0.555571f},
		{-0.707106f, - 0.000000f, - 0.707108f},
		{-0.555569f, - 0.000000f, - 0.831470f},
		{-0.382682f, - 0.000000f, - 0.923880f},
		{-0.195089f, - 0.000000f, - 0.980786f},
		{0.000002f, 2.000000f, - 1.000000f },
		{0.195092f, 2.000000f, - 0.980785f },
		{0.382685f, 2.000000f, - 0.923879f },
		{0.555572f, 2.000000f, - 0.831469f },
		{0.707108f, 2.000000f, - 0.707105f },
		{0.831471f, 2.000000f, - 0.555569f },
		{0.923880f, 2.000000f, - 0.382682f },
		{0.980786f, 2.000000f, - 0.195088f },
		{1.000000f, 2.000000f, 0.000002f},
		{0.980785f, 2.000000f, 0.195092f},
		{0.923879f, 2.000000f, 0.382685f},
		{0.831469f, 2.000000f, 0.555571f},
		{0.707106f, 2.000000f, 0.707107f},
		{0.555570f, 2.000000f, 0.831470f},
		{0.382684f, 2.000000f, 0.923879f},
		{0.195091f, 2.000000f, 0.980785f},
		{0.000001f, 2.000000f, 1.000000f},
		{- 0.195089f, 2.000000f, 0.980785f},
		{- 0.382682f, 2.000000f, 0.923880f},
		{- 0.555568f, 2.000000f, 0.831471f},
		{- 0.707105f, 2.000000f, 0.707108f},
		{- 0.831468f, 2.000000f, 0.555573f},
		{- 0.923878f, 2.000000f, 0.382686f},
		{- 0.980785f, 2.000000f, 0.195094f},
		{- 1.000000f, 2.000000f, 0.000004f},
		{- 0.980786f, 2.000000f,- 0.195086f},
		{- 0.923881f, 2.000000f,- 0.382679f},
		{- 0.831473f, 2.000000f,- 0.555566f},
		{- 0.707111f, 2.000000f,- 0.707103f},
		{- 0.555575f, 2.000000f,- 0.831466f},
		{- 0.382689f, 2.000000f,- 0.923877f},
		{- 0.195097f, 2.000000f,- 0.980784f}
	};
	
	vector<Float4> vn{
		{ 0,0,0 },
		{0.000000f, 0.000000f, - 0.999969f},
		{0.195074f, 0.000000f, - 0.980773f},
		{0.382672f, 0.000000f, - 0.923856f},
		{0.555559f, 0.000000f, - 0.831446f},
		{0.707083f, 0.000000f, - 0.707083f},
		{0.831446f, 0.000000f, - 0.555559f},
		{0.923856f, 0.000000f, - 0.382672f},
		{0.980773f, 0.000000f, - 0.195074f},
		{0.999969f, 0.000000f, 0.000000f},
		{0.980773f, 0.000000f, 0.195074f},
		{0.923856f, 0.000000f, 0.382672f},
		{0.831446f, 0.000000f, 0.555559f},
		{0.707083f, 0.000000f, 0.707083f},
		{0.555559f, 0.000000f, 0.831446f},
		{0.382672f, 0.000000f, 0.923856f},
		{0.195074f, 0.000000f, 0.980773f},
		{0.000000f, 0.000000f, 1.000000f},
		{- 0.195074f, 0.000000f, 0.980773f},
		{- 0.382672f, 0.000000f, 0.923856f},
		{- 0.555559f, 0.000000f, 0.831446f},
		{- 0.707083f, 0.000000f, 0.707083f},
		{- 0.831446f, 0.000000f, 0.555559f},
		{- 0.923856f, 0.000000f, 0.382672f},
		{- 0.980773f, 0.000000f, 0.195074f},
		{- 1.000000f, 0.000000f, 0.000000f},
		{- 0.980773f, 0.000000f, - 0.195074f},
		{- 0.923856f, 0.000000f, - 0.382672f},
		{- 0.831446f, 0.000000f, - 0.555559f},
		{- 0.707083f, 0.000000f, - 0.707083f},
		{- 0.555559f, 0.000000f, - 0.831446f},
		{- 0.382672f, 0.000000f, - 0.923856f},
		{- 0.195074f, 0.000000f, - 0.980773f}
	};

	m.triangles = vector<Triangle *>{
		new Triangle(new Vertex(v[1], vn[1]), new Vertex(v[33], vn[1]), new Vertex(v[34], vn[2])),
		new Triangle(new Vertex(v[1], vn[1]), new Vertex(v[34], vn[2]), new Vertex(v[2], vn[2])),
		new Triangle(new Vertex(v[2], vn[2]), new Vertex(v[34], vn[2]), new Vertex(v[35], vn[3])),
		new Triangle(new Vertex(v[2], vn[2]), new Vertex(v[35], vn[3]), new Vertex(v[3], vn[3])),
		new Triangle(new Vertex(v[3], vn[3]), new Vertex(v[35], vn[3]), new Vertex(v[36], vn[4])),
		new Triangle(new Vertex(v[3], vn[3]), new Vertex(v[36], vn[4]), new Vertex(v[4], vn[4])),
		new Triangle(new Vertex(v[4], vn[4]), new Vertex(v[36], vn[4]), new Vertex(v[37], vn[5])),
		new Triangle(new Vertex(v[4], vn[4]), new Vertex(v[37], vn[5]), new Vertex(v[5], vn[5])),
		new Triangle(new Vertex(v[5], vn[5]), new Vertex(v[37], vn[5]), new Vertex(v[38], vn[6])),
		new Triangle(new Vertex(v[5], vn[5]), new Vertex(v[38], vn[6]), new Vertex(v[6], vn[6])),
		new Triangle(new Vertex(v[6], vn[6]), new Vertex(v[38], vn[6]), new Vertex(v[39], vn[7])),
		new Triangle(new Vertex(v[6], vn[6]), new Vertex(v[39], vn[7]), new Vertex(v[7], vn[7])),
		new Triangle(new Vertex(v[7], vn[7]), new Vertex(v[39], vn[7]), new Vertex(v[40], vn[8])),
		new Triangle(new Vertex(v[7], vn[7]), new Vertex(v[40], vn[8]), new Vertex(v[8], vn[8])),
		new Triangle(new Vertex(v[8], vn[8]), new Vertex(v[40], vn[8]), new Vertex(v[41], vn[9])),
		new Triangle(new Vertex(v[8], vn[8]), new Vertex(v[41], vn[9]), new Vertex(v[9], vn[9])),
		new Triangle(new Vertex(v[9], vn[9]), new Vertex(v[41], vn[9]), new Vertex(v[42], vn[10])),
		new Triangle(new Vertex(v[9], vn[9]), new Vertex(v[42], vn[10]), new Vertex(v[10], vn[10])),
		new Triangle(new Vertex(v[10], vn[10]), new Vertex(v[42], vn[10]), new Vertex(v[43], vn[11])),
		new Triangle(new Vertex(v[10], vn[10]), new Vertex(v[43], vn[11]), new Vertex(v[11], vn[11])),
		new Triangle(new Vertex(v[11], vn[11]), new Vertex(v[43], vn[11]), new Vertex(v[44], vn[12])),
		new Triangle(new Vertex(v[11], vn[11]), new Vertex(v[44], vn[12]), new Vertex(v[12], vn[12])),
		new Triangle(new Vertex(v[12], vn[12]), new Vertex(v[44], vn[12]), new Vertex(v[45], vn[13])),
		new Triangle(new Vertex(v[12], vn[12]), new Vertex(v[45], vn[13]), new Vertex(v[13], vn[13])),
		new Triangle(new Vertex(v[13], vn[13]), new Vertex(v[45], vn[13]), new Vertex(v[46], vn[14])),
		new Triangle(new Vertex(v[13], vn[13]), new Vertex(v[46], vn[14]), new Vertex(v[14], vn[14])),
		new Triangle(new Vertex(v[14], vn[14]), new Vertex(v[46], vn[14]), new Vertex(v[47], vn[15])),
		new Triangle(new Vertex(v[14], vn[14]), new Vertex(v[47], vn[15]), new Vertex(v[15], vn[15])),
		new Triangle(new Vertex(v[15], vn[15]), new Vertex(v[47], vn[15]), new Vertex(v[48], vn[16])),
		new Triangle(new Vertex(v[15], vn[15]), new Vertex(v[48], vn[16]), new Vertex(v[16], vn[16])),
		new Triangle(new Vertex(v[16], vn[16]), new Vertex(v[48], vn[16]), new Vertex(v[49], vn[17])),
		new Triangle(new Vertex(v[16], vn[16]), new Vertex(v[49], vn[17]), new Vertex(v[17], vn[17])),
		new Triangle(new Vertex(v[17], vn[17]), new Vertex(v[49], vn[17]), new Vertex(v[50], vn[18])),
		new Triangle(new Vertex(v[17], vn[17]), new Vertex(v[50], vn[18]), new Vertex(v[18], vn[18])),
		new Triangle(new Vertex(v[18], vn[18]), new Vertex(v[50], vn[18]), new Vertex(v[51], vn[19])),
		new Triangle(new Vertex(v[18], vn[18]), new Vertex(v[51], vn[19]), new Vertex(v[19], vn[19])),
		new Triangle(new Vertex(v[19], vn[19]), new Vertex(v[51], vn[19]), new Vertex(v[52], vn[20])),
		new Triangle(new Vertex(v[19], vn[19]), new Vertex(v[52], vn[20]), new Vertex(v[20], vn[20])),
		new Triangle(new Vertex(v[20], vn[20]), new Vertex(v[52], vn[20]), new Vertex(v[53], vn[21])),
		new Triangle(new Vertex(v[20], vn[20]), new Vertex(v[53], vn[21]), new Vertex(v[21], vn[21])),
		new Triangle(new Vertex(v[21], vn[21]), new Vertex(v[53], vn[21]), new Vertex(v[54], vn[22])),
		new Triangle(new Vertex(v[21], vn[21]), new Vertex(v[54], vn[22]), new Vertex(v[22], vn[22])),
		new Triangle(new Vertex(v[22], vn[22]), new Vertex(v[54], vn[22]), new Vertex(v[55], vn[23])),
		new Triangle(new Vertex(v[22], vn[22]), new Vertex(v[55], vn[23]), new Vertex(v[23], vn[23])),
		new Triangle(new Vertex(v[23], vn[23]), new Vertex(v[55], vn[23]), new Vertex(v[56], vn[24])),
		new Triangle(new Vertex(v[23], vn[23]), new Vertex(v[56], vn[24]), new Vertex(v[24], vn[24])),
		new Triangle(new Vertex(v[24], vn[24]), new Vertex(v[56], vn[24]), new Vertex(v[57], vn[25])),
		new Triangle(new Vertex(v[24], vn[24]), new Vertex(v[57], vn[25]), new Vertex(v[25], vn[25])),
		new Triangle(new Vertex(v[25], vn[25]), new Vertex(v[57], vn[25]), new Vertex(v[58], vn[26])),
		new Triangle(new Vertex(v[25], vn[25]), new Vertex(v[58], vn[26]), new Vertex(v[26], vn[26])),
		new Triangle(new Vertex(v[26], vn[26]), new Vertex(v[58], vn[26]), new Vertex(v[59], vn[27])),
		new Triangle(new Vertex(v[26], vn[26]), new Vertex(v[59], vn[27]), new Vertex(v[27], vn[27])),
		new Triangle(new Vertex(v[27], vn[27]), new Vertex(v[59], vn[27]), new Vertex(v[60], vn[28])),
		new Triangle(new Vertex(v[27], vn[27]), new Vertex(v[60], vn[28]), new Vertex(v[28], vn[28])),
		new Triangle(new Vertex(v[28], vn[28]), new Vertex(v[60], vn[28]), new Vertex(v[61], vn[29])),
		new Triangle(new Vertex(v[28], vn[28]), new Vertex(v[61], vn[29]), new Vertex(v[29], vn[29])),
		new Triangle(new Vertex(v[29], vn[29]), new Vertex(v[61], vn[29]), new Vertex(v[62], vn[30])),
		new Triangle(new Vertex(v[29], vn[29]), new Vertex(v[62], vn[30]), new Vertex(v[30], vn[30])),
		new Triangle(new Vertex(v[30], vn[30]), new Vertex(v[62], vn[30]), new Vertex(v[63], vn[31])),
		new Triangle(new Vertex(v[30], vn[30]), new Vertex(v[63], vn[31]), new Vertex(v[31], vn[31])),
		new Triangle(new Vertex(v[31], vn[31]), new Vertex(v[63], vn[31]), new Vertex(v[64], vn[32])),
		new Triangle(new Vertex(v[31], vn[31]), new Vertex(v[64], vn[32]), new Vertex(v[32], vn[32])),
		new Triangle(new Vertex(v[33], vn[1]), new Vertex(v[1], vn[1]),  new Vertex(v[32], vn[32])),
		new Triangle(new Vertex(v[33], vn[1]), new Vertex(v[32], vn[32]),  new Vertex(v[64], vn[32]))
	};

	for (Triangle *t : m.triangles)
	{
		t->a->col = Color::GetRandom();
		m.vertices.push_back(t->a);
		t->b->col = Color::GetRandom();
		m.vertices.push_back(t->b);
		t->c->col = Color::GetRandom();
		m.vertices.push_back(t->c);
	}

	return m;
}

Mesh Mesh::HalfGeosphere()
{
	Mesh m;
	vector<Float4> v{
		{ 0.f,0.f,0 },
		{-0.309016973f, -0.9510566f,0.f  },
		{-0.809016824f, -0.587785423f,0.f  },
		{-0.525731206f, -0.723606944f, -0.447213203f   },
		{-1.f, 0.f, 0},
		{-0.809016824f, 0.587785423f, -0 },
		{-0.850650847f, 0.276393622f, -0.447213203f	  },
		{-0.309016973f, 0.9510566f, 0	  },
		{0.309016973f, 0.951056f, 0.f	 },
		{0.f, 0.894427359f, -0.447213203f,				 },
		{0.809016824f, 0.587785423f, -0.f },
		{1.f, 0.f, 0},
		{0.850650847f, 0.276393622f, -0.447213203f	 },
		{0.809016824f, -0.587785423f, 0	 },
		{0.309016973f, -0.9510566f, 0	 },
		{0.525731206f, -0.723606944f, -0.447213203f	 },
		{0.f, -0.850651026f, -0.52573061f},
		{-0.809017241f, -0.262865454f, -0.525730789f },
		{-0.49999997f, 0.688191354f, -0.525730729f	 },
		{0.49999997f, 0.688191354f, -0.525730729f		 },
		{0.809017241f, -0.262865454f, -0.525730789f	 },
		{0.f, 0.f, -1.f},
		{0.309017003f, -0.425325483f, -0.850650847f	},
		{-0.309017003f, -0.425325483f, -0.850650847f},
		{0.49999997f, 0.162460044f, -0.850650787f		},
		{0.f,0.525731087f, -0.850650787f				},
		{-0.49999997f, 0.162460044f, -0.850650787f	}
	};
	vector<Float4> vn{
		{0,0,0},
		{-0.294135749f, -0.929526031f, -0.22240822f	  },
		{-0.793138981f, -0.566979051f, -0.222408101f	  },
		{-0.525731146f, -0.723606884f, -0.447213322f	  },
		{-0.974924862f, -0.00749956351f, -0.222407967f },
		{-0.7843225f, 0.57911396f, -0.222408041f},
		{-0.850650847f, 0.276393473f, -0.447213322f},
		{-0.308400929f, 0.924891055f, -0.222408265f},
		{0.308400899f, 0.924891114f, -0.22240828f},
		{0, 0.894427299f, -0.447213531f,},
		{0.784322441f, 0.57911396f, -0.222408041f},
		{0.974924862f, -0.00749956351f, -0.222407967f },
		{0.850650907f, 0.276393473f, -0.447213322f },
		{0.793138981f, -0.566979051f, -0.222408086f },
		{0.294135749f, -0.929526031f, -0.22240822f },
		{0.525731146f, -0.723606884f, -0.447213382f },
		{0.00001f, -0.850650966f, -0.525730848f },
		{-0.809017241f, -0.262865484f, -0.525730908f },
		{-0.49999997f, 0.688191116f, -0.525730968f },
		{0.49999997f, 0.688191175f, -0.525730968f },
		{0.809017241f, -0.262865484f, -0.525730908f },
		{0, 0, -1.f },
		{0.309017062f, -0.425325513f, -0.850650728f },
		{-0.309017062f, -0.42532551f,3 - 0.850650728f },
		{0.50000006f, 0.162460059f, -0.850650728f },
		{0, 0.525731266f, -0.850650668f },
		{-0.500000119f, 0.162460059f, -0.850650728f },
	};
	

	m.triangles = vector<Triangle *>{
		new Triangle(new Vertex(v[3], vn[3]), new Vertex(v[1], vn[1]), new Vertex(v[2], vn[2])),
		new Triangle(new Vertex(v[6], vn[6]), new Vertex(v[4], vn[4]), new Vertex(v[5], vn[5])),
		new Triangle(new Vertex(v[9], vn[9]), new Vertex(v[7], vn[7]), new Vertex(v[8], vn[8])),
		new Triangle(new Vertex(v[12], vn[12]), new Vertex(v[10], vn[10]), new Vertex(v[11], vn[11])),
		new Triangle(new Vertex(v[15], vn[15]), new Vertex(v[13], vn[13]), new Vertex(v[14], vn[14])),
		new Triangle(new Vertex(v[16], vn[16]), new Vertex(v[1], vn[1]), new Vertex(v[3], vn[3])),
		new Triangle(new Vertex(v[15], vn[15]), new Vertex(v[14], vn[14]), new Vertex(v[16], vn[16])),
		new Triangle(new Vertex(v[14], vn[14]), new Vertex(v[1], vn[1]), new Vertex(v[16], vn[16])),
		new Triangle(new Vertex(v[17], vn[17]), new Vertex(v[4], vn[4]), new Vertex(v[6], vn[6])),
		new Triangle(new Vertex(v[3], vn[3]), new Vertex(v[2], vn[2]), new Vertex(v[17], vn[17])),
		new Triangle(new Vertex(v[2], vn[2]), new Vertex(v[4], vn[4]), new Vertex(v[17], vn[17])),
		new Triangle(new Vertex(v[18], vn[18]), new Vertex(v[7], vn[7]), new Vertex(v[9], vn[9])),
		new Triangle(new Vertex(v[6], vn[6]), new Vertex(v[5], vn[5]), new Vertex(v[18], vn[18])),
		new Triangle(new Vertex(v[5], vn[5]), new Vertex(v[7], vn[7]), new Vertex(v[18], vn[18])),
		new Triangle(new Vertex(v[19], vn[19]), new Vertex(v[10], vn[10]), new Vertex(v[12], vn[12])),
		new Triangle(new Vertex(v[9], vn[9]), new Vertex(v[8], vn[8]), new Vertex(v[19], vn[19])),
		new Triangle(new Vertex(v[8], vn[8]), new Vertex(v[10], vn[10]), new Vertex(v[19], vn[19])),
		new Triangle(new Vertex(v[20], vn[20]), new Vertex(v[13], vn[13]), new Vertex(v[15], vn[15])),
		new Triangle(new Vertex(v[12], vn[12]), new Vertex(v[11], vn[11]), new Vertex(v[20], vn[20])),
		new Triangle(new Vertex(v[11], vn[11]), new Vertex(v[13], vn[13]), new Vertex(v[20], vn[20])),
		new Triangle(new Vertex(v[23], vn[23]), new Vertex(v[21], vn[21]), new Vertex(v[22], vn[22])),
		new Triangle(new Vertex(v[16], vn[16]), new Vertex(v[22], vn[22]), new Vertex(v[15], vn[15])),
		new Triangle(new Vertex(v[3], vn[3]), new Vertex(v[23], vn[23]), new Vertex(v[16], vn[16])),
		new Triangle(new Vertex(v[23], vn[23]), new Vertex(v[22], vn[22]), new Vertex(v[16], vn[16])),
		new Triangle(new Vertex(v[22], vn[22]), new Vertex(v[21], vn[21]), new Vertex(v[24], vn[24])),
		new Triangle(new Vertex(v[20], vn[20]), new Vertex(v[24], vn[24]), new Vertex(v[12], vn[12])),
		new Triangle(new Vertex(v[15], vn[15]), new Vertex(v[22], vn[22]), new Vertex(v[20], vn[20])),
		new Triangle(new Vertex(v[22], vn[22]), new Vertex(v[24], vn[24]), new Vertex(v[20], vn[20])),
		new Triangle(new Vertex(v[24], vn[24]), new Vertex(v[21], vn[21]), new Vertex(v[25], vn[25])),
		new Triangle(new Vertex(v[19], vn[19]), new Vertex(v[25], vn[25]), new Vertex(v[9], vn[9])),
		new Triangle(new Vertex(v[12], vn[12]), new Vertex(v[24], vn[24]), new Vertex(v[19], vn[19])),
		new Triangle(new Vertex(v[24], vn[24]), new Vertex(v[25], vn[25]), new Vertex(v[19], vn[19])),
		new Triangle(new Vertex(v[25], vn[25]), new Vertex(v[21], vn[21]), new Vertex(v[26], vn[26])),
		new Triangle(new Vertex(v[18], vn[18]), new Vertex(v[26], vn[26]), new Vertex(v[6], vn[6])),
		new Triangle(new Vertex(v[9], vn[9]), new Vertex(v[25], vn[25]), new Vertex(v[18], vn[18])),
		new Triangle(new Vertex(v[25], vn[25]), new Vertex(v[26], vn[26]), new Vertex(v[18], vn[18])),
		new Triangle(new Vertex(v[26], vn[26]), new Vertex(v[21], vn[21]), new Vertex(v[23], vn[23])),
		new Triangle(new Vertex(v[17], vn[17]), new Vertex(v[23], vn[23]), new Vertex(v[3], vn[3])),
		new Triangle(new Vertex(v[6], vn[6]), new Vertex(v[26], vn[26]), new Vertex(v[17], vn[17])),
		new Triangle(new Vertex(v[26], vn[26]), new Vertex(v[23], vn[23]), new Vertex(v[17], vn[17]))
	};

	for (Triangle *t : m.triangles)
	{
		t->a->col = Color( 1, 0.6f,0.6f,0.6f );
		m.vertices.push_back(t->a);
		t->b->col = Color(1, 0.6f, 0.6f, 0.6f);
		m.vertices.push_back(t->b);
		t->c->col = Color(1, 0.6f, 0.6f, 0.6f);
		m.vertices.push_back(t->c);
	}
	return m;
}
