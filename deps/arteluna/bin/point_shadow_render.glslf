#version 330

  in float FragDepth;

void main()
{
  gl_FragDepth = FragDepth;
}  
