#include "MIHYCore_PCH.h"
#include "MIHYCore_DataStruct.h"


namespace MIHYCore{
    namespace DataStruct{

        

    std::string MIHYVector_UnitTest()
    {
        
#define VECTOR_PRINT(v) std::cout << "Capacity: " << v.get_capacity() << std::endl; for(UInt32 i = 0; i < v.get_size(); ++i) std::cout << v[i] << " "; std::cout << std::endl;
        using V = MIHYVector<Int32>;

        {//get_capacity
            V v{2};
            assert(v.get_capacity() == 2);
        }

        {//get_size
            V v{2, {0, 1, 2}};
            assert(v.get_size() == 3);
        }

        {//clear
            V v{2, {0, 1, 2}};
            assert(v.get_size() == 3);
            v.clear();
            assert(v.get_size() == 0);
        }

        {//operator[]
            V v{2, {0, 1, 2}};
            assert(v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        //생성자
        {   V v{10};   assert(v.get_capacity() == 10);  }

        {//생성자(초기화 리스트)
            V v{5, {0, 1, 2}};
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        };

        {//생성자(초기화 리스트, 시작 크기보다 많은 원소가 들어올 경우)
            V v{2, {0, 1, 2}};
            assert(v.get_capacity() > 2 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        };
        {//복사 생성자
            V o{5, {0, 1, 2}};
            V v{o};
            assert(o.get_capacity() == 5 && o.get_size() == 3 &&              //원본이 변하지 않았는지 확인.
                   o[0] == 0 && o[1] == 1 && o[2] == 2 &&
                   v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        {//이동 생성자
            V o{5, {0, 1, 2}};
            V v{std::move(o)}; 
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2 &&
                   o.get_size() == 0);                                         //이동 후 원본이 비어있는지 확인.

            o.push_back({3, 4, 5});                                                //이동 후 원본에 추가해도 정상 작동하는지 확인.
            assert(o.get_size() == 3 && o[0] == 3 && o[1] == 4 && o[2] == 5);
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&                   //이동 후 두 객체가 같은 메모리를 공유하지 않는지 확인.
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        {//대입
            V o{5, {0, 1, 2}};
            V v{2};
            v = o;
            assert(o.get_capacity() == 5 && o.get_size() == 3 &&              //원본이 변하지 않았는지 확인.
                   o[0] == 0 && o[1] == 1 && o[2] == 2 &&
                   v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }
    
        {//이동
            V o{5, {0, 1, 2}};
            V v{2}; 
            v = std::move(o);
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2 &&
                   o.get_size() == 0);                                         //이동 후 원본이 비어있는지 확인.

            o.push_back({3, 4, 5});                                                //이동 후 원본에 추가해도 정상 작동하는지 확인.
            assert(o.get_size() == 3 && o[0] == 3 && o[1] == 4 && o[2] == 5);
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&                   //이동 후 두 객체가 같은 메모리를 공유하지 않는지 확인.
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        {//Iterator 생성자

            V v{2, {0, 1, 2}};
            V::Iterator iterator{v.begin()};
            assert(*iterator == 0);
            
            V::Iterator iterator_copy{iterator};
            assert(*iterator_copy == 0);

            V::Iterator iterator_move{std::move(iterator_copy)};
            assert(*iterator_move == 0);

            V::Const_Iterator const_iterator{v.cbegin()};
            assert(*const_iterator == 0);

            V::Const_Iterator const_iterator_copy{const_iterator};
            assert(*const_iterator_copy == 0);

            V::Const_Iterator const_iterator_move{std::move(const_iterator_copy)};
            assert(*const_iterator_move == 0);

        }

        {//iterator
        
            V v{2, {0, 1, 2}};
            auto iterator{v.begin()};
            assert(*iterator == 0);
            ++iterator;
            assert(*iterator == 1);
            ++iterator;
            assert(*iterator == 2);
            --iterator;
            assert(*iterator == 1);
            --iterator;
            assert(*iterator == 0);
            iterator += 2;
            assert(*iterator == 2);
            assert(*(iterator - 2) == 0);
            iterator -= 2;
            assert(*iterator == 0);
            assert(*(iterator + 2) == 2);
            *iterator += 1;
            ++iterator;
            *iterator += 1;
            ++iterator;
            *iterator += 1;
            assert(v[0] == 1 && v[1] == 2 && v[2] == 3);

            v[0] = 0; v[1] = 1; v[2] = 2;
            auto const_iterator{v.cbegin()};
            assert(*const_iterator == 0);
            ++const_iterator;
            assert(*const_iterator == 1);
            ++const_iterator;
            assert(*const_iterator == 2);
            --const_iterator;
            assert(*const_iterator == 1);
            --const_iterator;
            assert(*const_iterator == 0);
            const_iterator += 2;
            assert(*const_iterator == 2);
            assert(*(const_iterator - 2) == 0);
            const_iterator -= 2;
            assert(*const_iterator == 0);
            assert(*(const_iterator + 2) == 2);

            v[0] = 0; v[1] = 1; v[2] = 2;
            auto reverse_iterator{v.rbegin()};
            assert(*reverse_iterator == 2);
            ++reverse_iterator;
            assert(*reverse_iterator == 1);
            ++reverse_iterator;
            assert(*reverse_iterator == 0);
            --reverse_iterator;
            assert(*reverse_iterator == 1);
            --reverse_iterator;
            assert(*reverse_iterator == 2);
            reverse_iterator += 2;
            assert(*reverse_iterator == 0);
            assert(*(reverse_iterator - 2) == 2);
            reverse_iterator -= 2;
            assert(*reverse_iterator == 2);
            assert(*(reverse_iterator + 2) == 0);
            *reverse_iterator += 1;
            ++reverse_iterator;
            *reverse_iterator += 1;
            ++reverse_iterator;
            *reverse_iterator += 1;
            assert(v[0] == 1 && v[1] == 2 && v[2] == 3);

            v[0] = 0; v[1] = 1; v[2] = 2;
            auto const_reverse_iterator{v.crbegin()};
            assert(*const_reverse_iterator == 2);
            ++const_reverse_iterator;
            assert(*const_reverse_iterator == 1);
            ++const_reverse_iterator;
            assert(*const_reverse_iterator == 0);
            --const_reverse_iterator;
            assert(*const_reverse_iterator == 1);
            --const_reverse_iterator;
            assert(*const_reverse_iterator == 2);
            const_reverse_iterator += 2;
            assert(*const_reverse_iterator == 0);
            assert(*(const_reverse_iterator - 2) == 2);
            const_reverse_iterator -= 2;
            assert(*const_reverse_iterator == 2);
            assert(*(const_reverse_iterator + 2) == 0);

            V temp{2};
            for(auto e : v){ temp.push_back(e); }
            assert(temp[0] == 0 && temp[1] == 1 && temp[2] == 2);

            temp.clear();
            for(auto e : v){ temp.push_back(e); }
            assert(temp[0] == 0 && temp[1] == 1 && temp[2] == 2);

            temp.clear();
            for(auto e : MIHYIterator_ForEach_Reverse<decltype(v)>(v)){ temp.push_back(e); }
            assert(temp[0] == 2 && temp[1] == 1 && temp[2] == 0);

            temp.clear();
            for(const auto e : MIHYIterator_ForEach_Reverse<decltype(v)>(v)){ temp.push_back(e); }
            assert(temp[0] == 2 && temp[1] == 1 && temp[2] == 0);
            
        }

        {//push_back
            V v{2};
            V v2{2, {3, 4}};
            V v3{2, {5, 6}};
            V v4{2, {7, 8}};
            v.push_back(0);
            v.push_back({1, 2});
            v.push_back(v2);
            v.push_back(std::move(v3));
            v.push_back(v4.begin(), v4.end());
            assert(v[0] == 0 && v[1] == 1 && v[2] == 2 && v[3] == 3 && v[4] == 4 && v[5] == 5 && v[6] == 6 && v[7] == 7 && v[8] == 8);
            assert(v2[0] == 3 && v2[1] == 4);
            //v3는 이동되기 때문에 size가 0입니다. 
            assert(v4[0] == 7 && v4[1] == 8);
            assert(v.get_size() == 9 && v2.get_size() == 2 && v3.get_size() == 0 && v4.get_size() == 2);
        }

        {//push front
            V v{2};
            V v2{2, {3, 4}};
            V v3{2, {5, 6}};
            V v4{2, {7, 8}};
            v.push_front(0);
            v.push_front({1, 2});
            v.push_front(v2);
            v.push_front(std::move(v3));
            v.push_front(v4.begin(), v4.end());
            assert(v[0] == 8 && v[1] == 7 && v[2] == 5 && v[3] == 6 && v[4] == 3 && v[5] == 4 && v[6] == 2 && v[7] == 1 && v[8] == 0);
            assert(v2[0] == 3 && v2[1] == 4);
            //v3는 이동되기 때문에 size가 0입니다. 
            assert(v4[0] == 7 && v4[1] == 8);
            assert(v.get_size() == 9 && v2.get_size() == 2 && v3.get_size() == 0 && v4.get_size() == 2);
        }

        // {//pop_back
        //     V v{2, {0, 1, 2}};
        //     v.pop_back();
        //     assert(v.get_size() == 2 && v[0] == 0 && v[1] == 1);
        // }

        // {//pop_front
        //     V v{2, {0, 1, 2}};
        //     v.pop_front();
        //     assert(v.get_size() == 2 && v[0] == 1 && v[1] == 2);
        // }

        // {//pop_at
        //     V v{2, {0, 1, 2}};
        //     v.pop_at(1);
        //     assert(v.get_size() == 2 && v[0] == 0 && v[1] == 2);
        // }

        return "Success";

    }


    }
}