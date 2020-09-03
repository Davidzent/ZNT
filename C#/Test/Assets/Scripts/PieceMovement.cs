using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Security.Cryptography;
using UnityEngine;

public class PieceMovement : MonoBehaviour
{
    private Vector3 mOffset;
    private float mZCoord;

    void OnMouseDown()
    {
        mZCoord = Camera.main.WorldToScreenPoint(gameObject.transform.position).z;
        mOffset = gameObject.transform.position - GetMouseWorldPos();
    }

    void OnMouseDrag()
    {
        transform.position = new Vector3(GetMouseWorldPos().x + mOffset.x,
            transform.position.y, GetMouseWorldPos().z + mOffset.z);
    }
    void OnMouseUp()
    {
        float tempX = (GetMouseWorldPos().x + mOffset.x) % 1.0f;
        float tempZ = (GetMouseWorldPos().z + mOffset.z) % 1.0f;
        if (tempX < 0.5)
        {
            transform.position = new Vector3(GetMouseWorldPos().x + mOffset.x + (0.5f-(tempX)%0.5f),
            transform.position.y, GetMouseWorldPos().z + mOffset.z);
        }
        else
        {
            transform.position = new Vector3(GetMouseWorldPos().x + mOffset.x - tempX % 0.5f,
            transform.position.y, GetMouseWorldPos().z + mOffset.z);
        }
        if (tempZ < 0.5)
        {
            transform.position = new Vector3(transform.position.x,
            transform.position.y, GetMouseWorldPos().z + mOffset.z + (0.5f - (tempZ) % 0.5f));
        }
        else
        {
            transform.position = new Vector3(transform.position.x,
            transform.position.y, GetMouseWorldPos().z + mOffset.z - tempZ % 0.5f);
        }
    }

    private Vector3 GetMouseWorldPos()
    {
        // pixel coordinates
        Vector3 mousePoint = Input.mousePosition;

        // z coordinate in game
        mousePoint.z = mZCoord;

        return Camera.main.ScreenToWorldPoint(mousePoint);
    }
     

}