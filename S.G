include
{
   preambleComment : < 'License.txt'
}

<search_range : (int) i->begin
                (int) i->end
                (search_rangeset)->subranges
>;

<search_rangeset : (search_range->array)+>;

<search_match : (text) t->pattern (int) i->flags
                (bool)->valid
                (search_rangeset)->ranges
>;

<action : (text) t->matchPat
          (text) t->replacePat
>;

<actionset : (action->array)+>;

