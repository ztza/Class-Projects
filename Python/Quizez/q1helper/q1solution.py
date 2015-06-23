#Toluwanimi Salako 30417945
from collections import defaultdict

def one_of(s:[]):
    def is_in(v):
        return (True if v in s else False)
    return is_in

def opposite_of(f):
    def opp(v):
        return (True if f(v) else False)
    return opp


def sort_names(data : [(str,str)]) -> [(str,str)]:
    return sorted(data, key = lambda x: (x[1], x[0]))

def sort_ages(data : [(str,(int,int,int))]) -> [(str,(int,int,int))]:
    return sorted(data, key = lambda x: (x[1][2], x[1][1], x[1][0]), reverse = True)


def big_family(d:{str:int}) -> [str]:
    return [i[0] for i in d.items() if i[1] > 2]
         

def only_child(d:{str:int}) -> {str:bool}:
    #Is this right? 
    return [{i[0]: i[1] == 0} for i in d.items() if i[1] == 0]
            
def follows1(s : str) -> {str:{str}}:
    result = dict();
    for p in range(0, len(s)):
        if p != len(s) -1:
            if s[p] in result.keys():
                result[s[p]].add(s[p+1])
            else:
                result[s[p]] = {s[p+1]}
    return result
        

def follows2(s : str) -> {str:{str}}:
    result = defaultdict(set);
    for p in range(0, len(s)):
        if p != len(s) -1:
            result[s[p]].add(s[p+1])
    return result

def reverse (d:{str:{str}}) -> {str:{str}}:
    result = defaultdict(set)
    for x in d.items():
        if len(x[1]) > 1:
            for i in x[1]:
                result[i].add(x[0])
        else:
            result[list(x[1])[0]].add(x[0])
    return result

if __name__ == '__main__':
    from goody import irange
    from predicate import is_prime
    import driver
   
    # Feel free to test other cases as well
    
    print('Testing one_of: is_vowel')
    is_vowel = one_of(['a','e','i','o','u'])
    print([(c,is_vowel(c)) for c in "tobeornottobe"])
        
    print('\nTesting opposite_of: is_composite')
    is_composite = opposite_of(is_prime)
    print(sorted({i:is_composite(i) for i in irange(2,10)}.items()))
         
    print('\nTesting opposite_of: is_consonant')
    is_consonant = opposite_of(is_vowel)
    print([(c,is_consonant(c)) for c in "tobeornottobe"])
         
    print('\nTesting sort_names: ')
    print(sort_names([('John','Smith'), ('Mary', 'Smith'),
                      ('Fred','Jones'), ('Frieda', 'Jones'),('Timothy', 'Jones')])) 
        
    print('\nTesting sort_ages:')
    print(sort_ages
          ([('Angie',(2,10,1954)),('Bob',(12,16,1949)),('Charlie',(9,4,1988)),
            ('Denise',(11,29,1990)),('Egon',(11, 22, 1924)),('Frances',(2,10,1954)),
            ('Gerald',(2,21,1920)),('Helen',(8,15,1924)),('Izzy',(12, 29, 1924)),
            ('Joyce',(2,21,1920))
             
            ]))  

    print('\nTesting big_family:')
    print(big_family(dict(Angie=2,Bob=5,Charlie=0,Denise=1,Egon=3,Frances=0, Gerald=2)))
 
    print('\nTesting only_child:')
    print(only_child(dict(Angie=2,Bob=5,Charlie=0,Denise=1,Egon=3,Frances=0, Gerald=2)))
     
    print('\nTesting follows:')
    print(follows1('bookeeper'))
    print(follows2('bookeeper'))
#     
    print('\nTesting reverse:')
    print(sorted(reverse({'Angie':{'plumbing', 'yardwork'},
                   'Bob': {'computers','carpentry'},
                   'Charlie': {'yardwork','carpentry','roofing'},
                   'Denise': {'computers','yardwork','roofing'},
                   'Egon': {'computers'},
                   'Frances': {'plumbing','carpentry', 'roofing'},
                    }).items()))
     
    print('\ndriver testing with batch_self_check:')
    driver.driver()
