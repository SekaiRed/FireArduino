//VectorClass
class Vector2 {
  public:
    Vector2(int myX, int myY);
    bool equals(Vector2 vec);
    byte x;
    byte y;
};

Vector2::Vector2(int myX, int myY)
{
  this->x = myX;
  this->y = myY;
}

bool Vector2::equals(Vector2 vec)
{
  if(this->x == vec.x && this->y == vec.y)
  return true;
  return false;
}
//////////////////

//InputClass
class Input {
  public:
    Input();
    Input(bool A, bool B,bool left, bool right, bool up, bool down);
    bool A = false;
    bool B = false;
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    bool anyDirectionDown();
    //bool anyInputDown();
};

Input::Input(bool A, bool B,bool left, bool right, bool up, bool down)
{
  this->A = A;
  this->B = B;
  this->left = left;
  this->right = right;
  this->up = up;
  this->down = down;
}

Input::Input(){}

bool Input::anyDirectionDown()
{
  return left || right || up || down;
}
//////////////////
