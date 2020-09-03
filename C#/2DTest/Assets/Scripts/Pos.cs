using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Reflection;
using UnityEngine;

public struct Pos
{
    public int x { get; set; }
    public int y { get; set; }

    public Pos(int x,int y)
        {
            this.x = x;
            this.y = y;
        } 
}
