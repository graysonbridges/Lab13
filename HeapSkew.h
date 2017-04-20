#if !defined HEAPSKEW_H
#define HEAPSKEW_H

#include "BinaryTree.h"
#include "wx/wx.h"

template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(wxDC& dc, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{ 
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew() 
{ 
   delete bt;
}  

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
        //DO THIS

        if(left->isEmpty())
        {
                delete left;
                return right;
        }
        if(right->isEmpty())
        {
                delete right;
                return left;
        }
        if((left->getRootItem()) < (right->getRootItem()))
        {
            bt =  merge(right, left); //should this be assigned to somethin
        }

        BinaryTree<T>* LL = left->detachLeftSubtree();
        BinaryTree<T>* LR = left->detachRightSubtree();

        left->attachLeftSubtree(LL);

        if(LR->isEmpty())
        {
                left->attachLeftSubtree(right);
                return left;
        }
        else
        {
                right = merge(LR, right);
                //left->attachLeftSubtree(right);
                return left;
        }
}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
        //DO THIS (calls merge, should be short)
        BinaryTree<T>* right = new BinaryTree<T>(item);
        BinaryTree<T>* left = bt;
        bt = merge(left, right);
        sze++;
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
        //DO THIS (calls merge, should be short)
        T* root = bt->getRootItem();
        BinaryTree<T>* left = bt->detachLeftSubtree();
        BinaryTree<T>* right = bt->detachRightSubtree();
        delete bt;
        bt = merge(left, right);
        sze--;
        return root;
}

template < class T >
void HeapSkew<T>::draw(wxDC& dc, int width, int height)
{
   bt->draw(dc, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
