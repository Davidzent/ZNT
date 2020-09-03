using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapManager : MonoBehaviour
{
    [SerializeField]
    private Map map1;

    // Start is called before the first frame update
    void Start()
    {
        map1.CreateLevel(20,20);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
