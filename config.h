#ifndef _CONFIG_H
#define _CONFIG_H

#include "ledger.h"

#include <iostream>
#include <memory>
#include <list>

namespace ledger {

class config_t
{
 public:
  // These options can all be set used text fields.

  strings_list  price_settings;
  std::string   init_file;
  std::string   data_file;
  std::string   cache_file;
  std::string   price_db;
  std::string   output_file;
  std::string   account;
  std::string   predicate;
  std::string   display_predicate;
  std::string   report_period;
  std::string   report_period_sort;
  std::string   format_string;
  std::string   balance_format;
  std::string   register_format;
  std::string   wide_register_format;
  std::string   plot_amount_format;
  std::string   plot_total_format;
  std::string   print_format;
  std::string   write_hdr_format;
  std::string   write_xact_format;
  std::string   equity_format;
  std::string   prices_format;
  std::string   pricesdb_format;
  std::string   date_format;
  std::string   sort_string;
  std::string   amount_expr;
  std::string   total_expr;
  std::string   total_expr_template;
  std::string   forecast_limit;
  std::string   reconcile_balance;
  std::string   reconcile_date;
  std::string   pager;
  unsigned long budget_flags;
  unsigned long pricing_leeway;
  int           head_entries;
  int           tail_entries;
  bool		show_collapsed;
  bool		show_subtotal;
  bool		show_totals;
  bool		show_related;
  bool		show_all_related;
  bool		show_inverted;
  bool		show_empty;
  bool		days_of_the_week;
  bool		by_payee;
  bool		comm_as_payee;
  bool		show_revalued;
  bool		show_revalued_only;
  bool		download_quotes;
  bool          use_cache;
  bool          cache_dirty;

  config_t() {
    reset();
  }
  config_t(const config_t&) {
    assert(0);
  }

  void reset();

  void regexps_to_predicate(const std::string& command,
			    std::list<std::string>::const_iterator begin,
			    std::list<std::string>::const_iterator end,
			    const bool account_regexp	       = false,
			    const bool add_account_short_masks = false,
			    const bool logical_and             = true);

  bool process_option(const std::string& opt, const char * arg = NULL);
  void process_arguments(int argc, char ** argv, const bool anywhere,
			 std::list<std::string>& args);
  void process_environment(char ** envp, const std::string& tag);

  void process_options(const std::string&     command,
		       strings_list::iterator arg,
		       strings_list::iterator args_end);

  item_handler<transaction_t> *
  chain_xact_handlers(const std::string& command,
		      item_handler<transaction_t> * base_formatter,
		      journal_t * journal,
		      account_t * master,
		      std::list<item_handler<transaction_t> *>& ptrs);
};

extern std::list<option_t> config_options;

void option_help(std::ostream& out);

struct declared_option_handler : public option_handler {
  declared_option_handler(const std::string& label,
			  const std::string& opt_chars) {
    add_option_handler(config_options, label, opt_chars, *this);
  }
};

#define OPT_BEGIN(tag, chars)						\
  static struct opt_ ## tag ## _handler					\
      : public declared_option_handler {				\
    opt_ ## tag ## _handler() : declared_option_handler(#tag, chars) {}	\
    virtual void operator()(const char * optarg)

#define OPT_END(tag) } opt_ ## tag ## _handler_obj

} // namespace ledger

#endif // _CONFIG_H
