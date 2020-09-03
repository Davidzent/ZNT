using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using UnityEngine;

// Cells
public enum CellState
{
    None,
    Friendly,
    Enemy,
    Free,
    OutOfBounds
}

public class Map : MonoBehaviour
{
    [SerializeField]
    private GameObject tile;

    public float TileSize
    {
        get { return tile.GetComponent<SpriteRenderer>().sprite.bounds.size.x; }
    }
    private int lengthX;
    private int lengthY;

    //Creates a Default Level
    public void CreateLevel(int lengtx, int lengty)
    {
        Vector3 worldStart = Camera.main.ScreenToWorldPoint(new Vector3(0, Screen.height));
        lengthX = lengtx;
        lengthY = lengty;
        for(int y = 0; y < lengthY; y++)
        {
            for (int x = 0; x < lengthX; x++)
            {
                PlaceTile(x, y,worldStart);
            }
        }
    }
    public void PlaceTile(int x,int y, Vector3 worldStart)
    {
        GameObject newTile = Instantiate(tile);
        newTile.transform.position = new Vector3(((TileSize -0.1f )* x), ((TileSize - 0.1f)* y));
    }
    /*public CellState ValidateCell(int targetX, int targetY)  //,BasePiece checkingPiece
    {
        // Bounds check
        if (targetX < 0 || targetX > (LengthX - 1))
            return CellState.OutOfBounds;

        if (targetY < 0 || targetY > (lengthY - 1))
            return CellState.OutOfBounds;

        // Get cell
        //Cell targetCell = mAllCells[targetX, targetY];

        // If the cell has a piece
        //if (targetCell.mCurrentPiece != null)
        //{
            /*
            // If friendly
            if (checkingPiece.mColor == targetCell.mCurrentPiece.mColor)
                return CellState.Friendly;

            // If enemy
            if (checkingPiece.mColor != targetCell.mCurrentPiece.mColor)
                return CellState.Enemy;
            
        //}

        return CellState.Free;
    }*/
}
