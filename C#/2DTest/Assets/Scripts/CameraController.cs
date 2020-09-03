using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{

    private float moveSpeed = 0.04f;
    private float scrollSpeed = 10f;
    [SerializeField]
    private GameObject tile;

    void Update()
    {
        if (Input.GetAxisRaw("Horizontal") != 0 || Input.GetAxisRaw("Vertical") != 0)
        {

            transform.position += moveSpeed * new Vector3(Input.GetAxisRaw("Horizontal"), Input.GetAxisRaw("Vertical"), 0 );
            if(transform.position.x < 0 || transform.position.x > tile.GetComponent<SpriteRenderer>().sprite.bounds.size.x*20)
            {
                transform.position -= moveSpeed * new Vector3(Input.GetAxisRaw("Horizontal"), 0, 0);
            }
            if (transform.position.y < 0 || transform.position.y > tile.GetComponent<SpriteRenderer>().sprite.bounds.size.y * 20)
            {
                transform.position -= moveSpeed * new Vector3(0, Input.GetAxisRaw("Vertical"), 0);
            }
        }

        if (Input.GetAxis("Mouse ScrollWheel") != 0)
        {
            transform.position += scrollSpeed * new Vector3(0, 0 , -Input.GetAxis("Mouse ScrollWheel"));
            if (transform.position.z > -5 || transform.position.z < -15)
            {
                transform.position -= scrollSpeed * new Vector3(0, 0, -Input.GetAxis("Mouse ScrollWheel"));
            }
        }
    }

}